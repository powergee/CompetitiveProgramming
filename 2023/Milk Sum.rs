use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let arr = io.isizes(n);
    let mut sorted = arr.clone();
    sorted.sort_unstable();

    let mut sum = vec![0; n];
    let mut pre_ans = sorted[0];
    for i in 1..n {
        pre_ans += (i + 1) as isize * sorted[i];
        sum[i] = sum[i - 1] + sorted[i];
    }

    let q = io.usize();
    for _ in 0..q {
        let (i, new) = (io.usize(), io.isize());
        let origin = arr[i - 1];

        let answer = if origin < new {
            // Ex)
            // origin(3)   new(8)
            // |           |
            // v           v
            // 3 3 3 5 6 7 9
            //   |       |
            //   ---dec---
            //
            // src = 0, dst = 6
            // pre_calc = 173
            // new_calc = 194
            // diff = dst * new - (src + 1) * origin - dec
            //      = 6*8 - 1*3 - (3+3+5+6+7)
            //      = 21
            let src = sorted.partition_point(|x| *x < origin);
            let dst = sorted.partition_point(|x| *x < new);
            debug_assert!(src < dst);

            pre_ans + dst as isize * new - (src as isize + 1) * origin - sum_excl(&sum, src, dst)
        } else if new < origin {
            // Ex 1)
            //   origin(9), new(6)
            //   |
            //   v
            // 1 9
            //
            // src = 1, dst = 1
            // diff = (dst + 1) * (new - origin)

            // Ex 2)
            // new(2)      origin(9)
            // |           |
            // v           v
            // 3 3 3 5 6 7 9
            // |         |
            // ----inc----
            //
            // src = 6, dst = 0
            // pre_calc = 173
            // new_calc = 139
            // diff = (dst + 1) * new - (src + 1) * origin + inc
            //      = 1*2 - 7*9 + (3+3+3+5+6+7)
            //      = -34
            let src = sorted.partition_point(|x| *x < origin);
            let dst = sorted.partition_point(|x| *x < new);
            debug_assert!(dst <= src);

            if src == dst {
                pre_ans + (dst as isize + 1) * (new - origin)
            } else {
                pre_ans + (dst as isize + 1) * new - (src as isize + 1) * origin
                    + sum_excl(&sum, dst, src)
                    + sorted[dst]
            }
        } else {
            pre_ans
        };

        writeln!(io.writer, "{answer}").unwrap();
    }
}

fn sum_excl(sum: &[isize], left: usize, right: usize) -> isize {
    if left + 1 < right {
        sum[right - 1] - sum[left]
    } else {
        0
    }
}

/// Modified EbTech's Scanner
pub struct IO<R, W: Write> {
    reader: R,
    writer: BufWriter<W>,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
}

impl IO<StdinLock<'static>, StdoutLock<'static>> {
    pub fn stdio() -> Self {
        Self::new(stdin().lock(), stdout().lock())
    }
}

impl<R: BufRead, W: Write> IO<R, W> {
    pub fn new(reader: R, writer: W) -> Self {
        Self {
            reader,
            writer: BufWriter::new(writer),
            buf_str: String::new(),
            buf_iter: "".split_whitespace(),
        }
    }

    #[inline]
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader
                .read_line(&mut self.buf_str)
                .expect("Failed read");
            self.buf_iter = unsafe { std::mem::transmute(self.buf_str.split_whitespace()) };
        }
    }
}

macro_rules! io_shortcut {
    ($scan_type:ident, $single_ident:ident, $multi_ident:ident) => {
        impl<R: BufRead, W: Write> IO<R, W> {
            #[inline]
            #[allow(unused)]
            fn $single_ident(&mut self) -> $scan_type {
                self.next()
            }
            #[inline]
            #[allow(unused)]
            fn $multi_ident(&mut self, n: usize) -> Vec<$scan_type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    };
}
io_shortcut!(usize, usize, usizes);
io_shortcut!(isize, isize, isizes);

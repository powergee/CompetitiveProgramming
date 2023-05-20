use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let (n, m) = (io.usize(), io.usize());
    let map = (0..n)
        .map(|_| {
            io.string()
                .bytes()
                .map(|b| if b == '0' as u8 { false } else { true })
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();
    let mut left = vec![vec![0; m]; n];
    let mut right = vec![vec![0; m]; n];

    for c in 0..m {
        let init = if map[n - 1][c] { 1 } else { 0 };
        left[n - 1][c] = init;
        right[n - 1][c] = init;
    }
    for r in 0..n {
        left[r][0] = if map[r][0] { 1 } else { 0 };
        right[r][m - 1] = if map[r][m - 1] { 1 } else { 0 };
    }
    for r in (0..n - 1).rev() {
        for c in 1..m {
            left[r][c] = if map[r][c] { left[r + 1][c - 1] + 1 } else { 0 };
        }
        for c in 0..m - 1 {
            right[r][c] = if map[r][c] {
                right[r + 1][c + 1] + 1
            } else {
                0
            };
        }
    }

    let mut answer = 0;
    for i in 0..n {
        for j in 0..m {
            for k in 1.max(answer + 1)..=left[i][j].min(right[i][j]) {
                if left[i + k - 1][j + k - 1] >= k && right[i + k - 1][j + 1 - k] >= k {
                    answer = answer.max(k);
                }
            }
        }
    }
    writeln!(io.writer, "{answer}").unwrap();
}

// Modified EbTech's Scanner
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
io_shortcut!(String, string, strings);

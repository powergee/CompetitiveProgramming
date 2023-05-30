use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let (n, q) = (io.usize(), io.usize());
    let map = (0..n).map(|_| io.usizes(n)).collect::<Vec<_>>();
    let mut right_sum = vec![vec![0; n]; n];
    let mut right_sum_col_min = vec![vec![0; n]; n];

    for r in 0..n {
        right_sum[r][n - 1] = map[r][n - 1];
        for c in (0..n - 1).rev() {
            right_sum[r][c] = map[r][c] + right_sum[r][c + 1];
        }
    }
    for c in 0..n {
        right_sum_col_min[0][c] = right_sum[0][c];
        for r in 1..n {
            right_sum_col_min[r][c] = right_sum_col_min[r - 1][c].min(right_sum[r][c]);
        }
    }

    for _ in 0..q {
        let (sr, sc, l) = (io.usize() - 1, io.usize() - 1, io.usize());
        let mut result = right_sum[sr][sc];
        for c in sc..n {
            result =
                result.min((right_sum[sr][sc] - right_sum[sr][c]) + right_sum_col_min[sr - l][c]);
        }
        writeln!(io.writer, "{result}").unwrap();
    }
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

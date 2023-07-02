use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let (n, m) = (io.usize(), io.usize());
    let arr = io.i64s(n);

    // dp[start][remaining_groups][is_prev_selected]
    let mut dp = vec![vec![vec![i64::MIN / 2; 2]; m + 1]; n + 1];
    for prev_sel in 0..2 {
        dp[n][0][prev_sel] = 0
    }

    for start in (0..n).rev() {
        dp[start][0][0] = dp[start + 1][0][0];
        dp[start][0][1] = dp[start + 1][0][0].max(arr[start] + dp[start + 1][0][1]);
        for groups in 1..m + 1 {
            dp[start][groups][0] =
                dp[start + 1][groups][0].max(arr[start] + dp[start + 1][groups - 1][1]);
            dp[start][groups][1] =
                dp[start + 1][groups][0].max(arr[start] + dp[start + 1][groups][1]);
        }
    }

    writeln!(io.writer, "{}", dp[0][m][0]).unwrap();
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

macro_rules! io_shortcut {(
    $(($type:ident, $types:ident))*
) => (
    $(
        impl<R: BufRead, W: Write> IO<R, W> {
            #[inline]
            #[allow(unused)]
            fn $type(&mut self) -> $type {
                self.next()
            }
            #[inline]
            #[allow(unused)]
            fn $types(&mut self, n: usize) -> Vec<$type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    )*
)}

io_shortcut! {
    (u8, u8s) (u16, u16s) (u32, u32s) (u64, u64s) (u128, u128s)
    (i8, i8s) (i16, i16s) (i32, i32s) (i64, i64s) (i128, i128s)
    (usize, usizes)
}

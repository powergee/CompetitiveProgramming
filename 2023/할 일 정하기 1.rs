use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let cost = (0..n)
        .map(|_| (0..n).map(|_| io.usize()).collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut avails = vec![vec![]; n + 1];
    for avail in 0usize..(1 << n) {
        avails[avail.count_ones() as usize].push(avail);
    }

    let mut dp = vec![vec![0; 1 << n]; n + 1];
    for i in (0..n).rev() {
        for &avail in &avails[n - i] {
            dp[i][avail] = usize::MAX;
            for j in 0..n {
                if (avail & (1 << j)) > 0 {
                    let next_avail = avail & !(1 << j);
                    dp[i][avail] = dp[i][avail].min(dp[i + 1][next_avail] + cost[i][j]);
                }
            }
        }
    }

    writeln!(io.writer, "{}", dp[0][(1 << n) - 1]).unwrap();
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

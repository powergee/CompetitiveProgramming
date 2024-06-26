use std::{
    collections::HashSet,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
    mem::take,
};

fn main() {
    let mut io = IO::stdio();
    let (n, q) = (io.usize(), io.usize());

    let mut sets = (0..n)
        .map(|_| {
            let n = io.usize();
            io.usizes(n).into_iter().collect::<HashSet<_>>()
        })
        .collect::<Vec<_>>();

    for _ in 0..q {
        match io.usize() {
            1 => {
                let (a, b) = (io.usize() - 1, io.usize() - 1);
                if sets[a].len() > sets[b].len() {
                    let sub = take(&mut sets[b]);
                    sets[a].extend(sub);
                } else {
                    let sub = take(&mut sets[a]);
                    sets[b].extend(sub);
                    sets.swap(a, b);
                }
            }
            2 => {
                let a = io.usize() - 1;
                writeln!(io.writer, "{}", sets[a].len()).unwrap();
            }
            _ => unreachable!(),
        }
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

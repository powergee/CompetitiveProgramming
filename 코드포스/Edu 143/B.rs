#![allow(unused)]
use std::{io::{BufRead, BufWriter, Write}, collections::VecDeque};

fn main() {
    let stdin = std::io::stdin();
    let stdout = std::io::stdout();
    let io = &mut IO::new(stdin.lock(), stdout.lock());

    let tt = io.usize();
    for _ in 0..tt {
        let (n, k) = (io.usize(), io.usize());
        let segs = (0..n).map(|_| (io.usize(), io.usize())).collect::<Vec<_>>();
        
        let mut yes = false;
        if segs.iter().filter(|(a, b)| *a == k && *b == k).count() > 0 {
            yes = true;
        }
        for &(a1, b1) in &segs {
            for &(a2, b2) in &segs {
                if a1 == k && b2 == k {
                    yes = true;
                }
                if a2 == k && b1 == k {
                    yes = true;
                }
            }
        }

        writeln!(io.writer, "{}", if yes { "YES" } else { "NO" }).unwrap();
    }
}

// Modified EbTech's Scanner
pub struct IO<R, W: Write> {
    reader: R,
    writer: BufWriter<W>,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
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
io_shortcut!(i64, i64, i64s);
io_shortcut!(u64, u64, u64s);
io_shortcut!(usize, usize, usizes);
io_shortcut!(f64, f64, f64s);
io_shortcut!(String, string, strings);

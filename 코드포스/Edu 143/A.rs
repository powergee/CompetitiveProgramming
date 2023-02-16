#![allow(unused)]
use std::{io::{BufRead, BufWriter, Write}, collections::VecDeque};

fn main() {
    let stdin = std::io::stdin();
    let stdout = std::io::stdout();
    let io = &mut IO::new(stdin.lock(), stdout.lock());

    let tt = io.usize();
    for _ in 0..tt {
        let (n, m) = (io.usize(), io.usize());
        let mut a = io.string().chars().collect::<Vec<_>>();
        let mut b = io.string().chars().collect::<Vec<_>>();
        
        b.reverse();
        a.append(&mut b);
        
        while a.len() > 1 {
            if a[a.len()-1] != a[a.len()-2] {
                let _ = a.pop();
            } else {
                break;
            }
        }
        a.reverse();
        while a.len() > 1 {
            if a[a.len()-1] != a[a.len()-2] {
                let _ = a.pop();
            } else {
                break;
            }
        }

        if a.len() <= 2 {
            writeln!(io.writer, "YES").unwrap();
        } else {
            writeln!(io.writer, "NO").unwrap();
        }
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

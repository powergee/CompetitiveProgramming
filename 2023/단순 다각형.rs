use std::{
    cmp::Ordering,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let t = io.usize();
    for _ in 0..t {
        let n = io.usize();
        let mut points = (0..n).map(|i| (io.i64(), io.i64(), i)).collect::<Vec<_>>();
        let start = *points.iter().min().unwrap();
        points.sort_by(|p1, p2| {
            let comp = ccw(&start, p1, p2);
            if comp == 0 {
                dist(&start, p1).cmp(&dist(&start, p2))
            } else if comp > 0 {
                Ordering::Less
            } else {
                Ordering::Greater
            }
        });
        for i in (0..n).rev() {
            if ccw(&start, points.last().unwrap(), &points[i]) != 0 {
                let mut parts = points.drain(i + 1..).rev().collect();
                points.append(&mut parts);
                break;
            }
        }
        writeln!(
            io.writer,
            "{}",
            points
                .iter()
                .map(|(_, _, i)| i.to_string())
                .collect::<Vec<_>>()
                .join(" ")
        )
        .unwrap();
    }
}

type Point = (i64, i64, usize);

fn ccw(p1: &Point, p2: &Point, p3: &Point) -> i64 {
    p1.0 * p2.1 + p2.0 * p3.1 + p3.0 * p1.1 - p1.1 * p2.0 - p2.1 * p3.0 - p3.1 * p1.0
}

fn dist(p1: &Point, p2: &Point) -> i64 {
    (p1.0 - p2.0).pow(2) + (p1.1 - p2.1).pow(2)
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
io_shortcut!(i64, i64, i64s);

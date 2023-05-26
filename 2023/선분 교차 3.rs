use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};
use std::mem::swap;

fn main() {
    let mut io = IO::stdio();
    let (x1, y1, x2, y2) = (io.next(), io.next(), io.next(), io.next());
    let (x3, y3, x4, y4) = (io.next(), io.next(), io.next(), io.next());
    let l1 = Line::new(x1, y1, x2, y2);
    let l2 = Line::new(x3, y3, x4, y4);

    match l1.cross(&l2) {
        Ok(Some((x, y))) => writeln!(io.writer, "1\n{:.10} {:.10}", x, y).unwrap(),
        Ok(None) => writeln!(io.writer, "1").unwrap(),
        Err(()) => writeln!(io.writer, "0").unwrap(),
    }
}

fn ccw(p1: &(i64, i64), p2: &(i64, i64), p3: &(i64, i64)) -> i64 {
    let val = p1.0 * p2.1 + p2.0 * p3.1 + p3.0 * p1.1 - p1.1 * p2.0 - p2.1 * p3.0 - p3.1 * p1.0;
    val.checked_div(val.abs()).unwrap_or(0)
}

struct Line<T> {
    p1: (T, T),
    p2: (T, T),
}

impl Line<i64> {
    fn new(x1: i64, y1: i64, x2: i64, y2: i64) -> Self {
        let mut result = Self {
            p1: (x1, y1),
            p2: (x2, y2),
        };
        if result.p1 > result.p2 {
            swap(&mut result.p1, &mut result.p2);
        }
        result
    }

    fn cross(&self, other: &Self) -> Result<Option<(f64, f64)>, ()> {
        let ccw1 = ccw(&self.p1, &self.p2, &other.p1) * ccw(&self.p1, &self.p2, &other.p2);
        let ccw2 = ccw(&other.p1, &other.p2, &self.p1) * ccw(&other.p1, &other.p2, &self.p2);

        if ccw1 == 0 && ccw2 == 0 {
            if self.p1 <= other.p2 && other.p1 <= self.p2 {
                Ok(self.cross_unchecked(other))
            } else {
                Err(())
            }
        } else if ccw1 <= 0 && ccw2 <= 0 {
            Ok(self.cross_unchecked(other))
        } else {
            Err(())
        }
    }

    fn cross_unchecked(&self, other: &Self) -> Option<(f64, f64)> {
        let px = (self.p1.0 * self.p2.1 - self.p1.1 * self.p2.0) * (other.p1.0 - other.p2.0)
            - (self.p1.0 - self.p2.0) * (other.p1.0 * other.p2.1 - other.p1.1 * other.p2.0);
        let py = (self.p1.0 * self.p2.1 - self.p1.1 * self.p2.0) * (other.p1.1 - other.p2.1)
            - (self.p1.1 - self.p2.1) * (other.p1.0 * other.p2.1 - other.p1.1 * other.p2.0);
        let p = (self.p1.0 - self.p2.0) * (other.p1.1 - other.p2.1)
            - (self.p1.1 - self.p2.1) * (other.p1.0 - other.p2.0);

        if p == 0 {
            if self.p2 == other.p1 && self.p1 <= other.p1 {
                Some((self.p2.0 as _, self.p2.1 as _))
            } else if self.p1 == other.p2 && other.p1 <= self.p1 {
                Some((self.p1.0 as _, self.p1.1 as _))
            } else {
                None
            }
        } else {
            Some((px as f64 / p as f64, py as f64 / p as f64))
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

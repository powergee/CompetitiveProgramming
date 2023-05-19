use std::ops::Bound::{Included, Unbounded};
use std::{
    collections::BTreeSet,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let (n, _) = (io.usize(), io.usize());
    let edges = (0..n).map(|_| (io.usize(), io.usize())).collect::<Vec<_>>();

    let max_length = {
        let is_possible = |length: usize| {
            let mut ts = 0;
            let mut xs = BTreeSet::new();
            let mut ys = BTreeSet::new();
            for i in 0..length - 1 {
                xs.insert((edges[i].0, ts + 1));
                ys.insert((edges[i].1, ts + 2));
                ts += 2;
            }
            for i in length - 1..n {
                xs.insert((edges[i].0, ts + 1));
                ys.insert((edges[i].1, ts + 2));
                ts += 2;

                if xs.iter().next_back().unwrap().0 <= ys.iter().next().unwrap().0 {
                    return true;
                }

                let x_remove = xs
                    .range((Included((edges[i + 1 - length].0, 0)), Unbounded))
                    .next()
                    .unwrap()
                    .clone();
                xs.remove(&x_remove);
                let y_remove = ys
                    .range((Included((edges[i + 1 - length].1, 0)), Unbounded))
                    .next()
                    .unwrap()
                    .clone();
                ys.remove(&y_remove);
            }
            false
        };

        let mut left = 1;
        let mut right = n;
        while left + 1 < right {
            let mid = (left + right) / 2;
            if is_possible(mid) {
                left = mid;
            } else {
                right = mid;
            }
        }
        if is_possible(right) {
            left = right;
        }
        left
    };

    let count = {
        let mut ts = 0;
        let mut xs = BTreeSet::new();
        let mut ys = BTreeSet::new();
        let mut points = vec![];
        for i in 0..max_length - 1 {
            xs.insert((edges[i].0, ts + 1));
            ys.insert((edges[i].1, ts + 2));
            ts += 2;
        }
        for i in max_length - 1..n {
            xs.insert((edges[i].0, ts + 1));
            ys.insert((edges[i].1, ts + 2));
            ts += 2;

            let range = (
                xs.iter().next_back().unwrap().0,
                ys.iter().next().unwrap().0,
            );
            if range.0 <= range.1 {
                points.push((range.0, 0));
                points.push((range.1, 1));
            }

            let x_remove = xs
                .range((Included((edges[i + 1 - max_length].0, 0)), Unbounded))
                .next()
                .unwrap()
                .clone();
            xs.remove(&x_remove);
            let y_remove = ys
                .range((Included((edges[i + 1 - max_length].1, 0)), Unbounded))
                .next()
                .unwrap()
                .clone();
            ys.remove(&y_remove);
        }
        points.sort();

        let mut total = 0;
        let mut count = 0;
        let mut start = 0;
        for p in points {
            if p.1 == 0 {
                count += 1;
                if count == 1 {
                    start = p.0;
                }
            } else {
                count -= 1;
                if count == 0 {
                    total += p.0 - start + 1;
                }
            }
        }
        total
    };

    writeln!(io.writer, "{max_length} {count}").unwrap();
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

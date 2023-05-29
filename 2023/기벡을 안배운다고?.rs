use std::{
    collections::HashMap,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();

    let mut count: HashMap<(i64, i64), usize> = HashMap::new();
    let mut answer = 0;
    let mut zero = 0;
    for i in 0..n {
        let (a, b) = (io.i64(), io.i64());
        if a == 0 && b == 0 {
            answer += i;
            zero += 1;
        } else {
            let ort1 = unit((-b, a));
            let ort2 = unit((b, -a));
            answer += count.get(&ort1).unwrap_or(&0) + count.get(&ort2).unwrap_or(&0) + zero;
            *count.entry(unit((a, b))).or_insert(0) += 1;
        }
    }
    writeln!(io.writer, "{answer}").unwrap();
}

fn unit((x, y): (i64, i64)) -> (i64, i64) {
    let gcd = gcd(x.abs(), y.abs());
    (x / gcd, y / gcd)
}

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 {
        a
    } else {
        gcd(b, a % b)
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
io_shortcut!(i64, i64, i64s);

use std::{
    collections::BTreeSet,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let mut ops = Vec::with_capacity(n);
    let mut tallest = 0;
    let mut bounds = BTreeSet::new();
    for _ in 0..n {
        let (op, x) = (io.u8(), io.usize());
        if op == 1 {
            tallest = x;
            ops.push(Op::Add(x));
        } else {
            let bound = tallest.saturating_sub(x);
            tallest = bound;
            let key = (bound, bounds.len());
            bounds.insert(key);
            ops.push(Op::Cut(key));
        }
    }

    let mut answer = 0;
    for op in ops {
        match op {
            Op::Add(x) => answer += x.min(bounds.first().map(|b| b.0).unwrap_or(usize::MAX)),
            Op::Cut(key) => assert!(bounds.remove(&key)),
        }
    }

    writeln!(io.writer, "{answer}").unwrap();
}

enum Op {
    Add(usize),
    Cut((usize, usize)),
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
            #[allow(unused)]
            fn $type(&mut self) -> $type {
                self.next()
            }
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
    (usize, usizes) (isize, isizes) (f64, f64s)
}

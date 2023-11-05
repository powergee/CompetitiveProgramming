use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let poles = io.u64s(n);
    let mut costs = vec![0; n];

    let mut stack: Vec<(usize, u64)> = vec![];
    let ranges: [&mut dyn Iterator<Item = usize>; 2] = [&mut (0..n), &mut (0..n).rev()];
    for range in ranges {
        for i in range {
            while let Some(prev) = stack.last().copied() {
                let prev_index = prev.0;
                if poles[prev_index] < poles[i] {
                    stack.pop();
                } else {
                    break;
                }
            }
            if let Some((pi, acc)) = stack.last().copied() {
                stack.push((
                    i,
                    acc + (poles[pi] - poles[i]).pow(2) + i.abs_diff(pi).pow(2) as u64,
                ));
            } else {
                stack.push((i, 0));
            }
            costs[i] += stack.last().unwrap().1;
        }
        stack.clear();
    }

    let q = io.usize();
    for p in io.usizes(q) {
        writeln!(io.writer, "{}", costs[p - 1]).unwrap();
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

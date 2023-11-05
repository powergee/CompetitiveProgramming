use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let nums = (0..n).map(|_| io.usize() == 2).collect::<Vec<_>>();
    let mut parts = vec![(nums[0], 1usize)];
    for v in nums.into_iter().skip(1) {
        let last = parts.last().copied().unwrap();
        if last.0 == v {
            parts.last_mut().unwrap().1 += 1;
            continue;
        }
        if !last.0 && last.1 % 2 == 0 {
            let tail = parts.pop().unwrap();
            debug_assert!(parts.last().map(|prev| prev.0).unwrap_or(true));
            let merged = parts.pop().map(|prev| prev.1).unwrap_or(0) + tail.1 / 2 + 1;
            parts.push((true, merged));
        } else {
            parts.push((v, 1));
        }
    }

    let mut answer = parts
        .iter()
        .fold(1, |max, curr| max.max(if curr.0 { 2 } else { 1 }));
    for i in 0..parts.len() {
        if !parts[i].0 {
            answer = answer.max(1 << parts[i].1.ilog2());
            continue;
        }
        let left = if i > 0 { parts[i - 1].1 / 2 } else { 0 };
        let right = if i + 1 < parts.len() {
            parts[i + 1].1 / 2
        } else {
            0
        };
        let twos = left + parts[i].1 + right;
        answer = answer.max(1 << (1 + twos.ilog2()));
    }

    writeln!(io.writer, "{answer}").unwrap();
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

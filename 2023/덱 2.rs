use std::{
    collections::VecDeque,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let mut deque = VecDeque::new();
    for _ in 0..n {
        match io.usize() {
            1 => deque.push_front(io.i32()),
            2 => deque.push_back(io.i32()),
            3 => writeln!(io.writer, "{}", deque.pop_front().unwrap_or(-1)).unwrap(),
            4 => writeln!(io.writer, "{}", deque.pop_back().unwrap_or(-1)).unwrap(),
            5 => writeln!(io.writer, "{}", deque.len()).unwrap(),
            6 => writeln!(io.writer, "{}", if deque.is_empty() { 1 } else { 0 }).unwrap(),
            7 => writeln!(io.writer, "{}", deque.front().copied().unwrap_or(-1)).unwrap(),
            8 => writeln!(io.writer, "{}", deque.back().copied().unwrap_or(-1)).unwrap(),
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
            writer: BufWriter::with_capacity(5000000, writer),
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
io_shortcut!(i32, i32, i32s);

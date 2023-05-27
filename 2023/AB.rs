use std::{
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
    iter::repeat,
    mem::{transmute, zeroed, MaybeUninit},
};

fn main() {
    let mut io = IO::stdio();
    let q = io.usize();
    let mut at = Trie::empty();
    let mut bt = Trie::empty();

    for _ in 0..q {
        let com = io.string();
        let arg = io.string();
        match (com.as_str(), arg.as_str()) {
            ("add", "A") => at.insert(io.string().as_bytes().iter().map(|b| (*b - b'a') as usize)),
            ("add", "B") => bt.insert(
                io.string()
                    .as_bytes()
                    .iter()
                    .rev()
                    .map(|b| (*b - b'a') as usize),
            ),
            ("delete", "A") => {
                at.delete(io.string().as_bytes().iter().map(|b| (*b - b'a') as usize))
            }
            ("delete", "B") => bt.delete(
                io.string()
                    .as_bytes()
                    .iter()
                    .rev()
                    .map(|b| (*b - b'a') as usize),
            ),
            ("find", s) => {
                let mut total = 0;
                let acnt = at.collect_count(s.as_bytes().iter().map(|b| (*b - b'a') as usize));
                let bcnt =
                    bt.collect_count(s.as_bytes().iter().rev().map(|b| (*b - b'a') as usize));
                for (a, b) in acnt.iter().zip(bcnt.iter().rev().skip(1)) {
                    total += a * b;
                }
                writeln!(io.writer, "{total}").unwrap();
            }
            _ => unreachable!(),
        }
    }
}

struct Trie {
    next: [Option<Box<Trie>>; 26],
    count: usize,
}

impl Trie {
    fn empty() -> Self {
        let mut next: [MaybeUninit<Option<Box<Trie>>>; 26] = unsafe { zeroed() };
        for n in next.iter_mut() {
            n.write(None);
        }
        Self {
            next: unsafe { transmute(next) },
            count: 0,
        }
    }

    fn insert(&mut self, mut iter: impl Iterator<Item = usize>) {
        self.count += 1;
        if let Some(idx) = iter.next() {
            self.next[idx]
                .get_or_insert(Box::new(Self::empty()))
                .insert(iter);
        }
    }

    fn delete(&mut self, mut iter: impl Iterator<Item = usize>) {
        self.count -= 1;
        if let Some(idx) = iter.next() {
            self.next[idx].as_mut().unwrap().delete(iter);
        }
    }

    fn collect_count(&self, iter: impl Iterator<Item = usize>) -> Vec<usize> {
        let mut result = vec![];
        self.collect_count_inner(iter, &mut result);
        result
    }

    fn collect_count_inner(&self, mut iter: impl Iterator<Item = usize>, result: &mut Vec<usize>) {
        if let Some(idx) = iter.next() {
            match self.next[idx].as_ref() {
                Some(next) => {
                    result.push(next.count);
                    next.collect_count_inner(iter, result);
                }
                None => {
                    result.push(0);
                    result.extend(repeat(0).take(iter.count()))
                }
            };
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
io_shortcut!(String, string, strings);

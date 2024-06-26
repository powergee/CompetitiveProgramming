use std::{
    cell::{Cell, RefCell},
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
    mem::size_of,
};

fn main() {
    let mut io = IO::stdio();
    let trie = Trie::default();
    trie.insert(0);

    let m = io.usize();

    for _ in 0..m {
        let (op, x) = (io.usize(), io.next());
        match op {
            1 => trie.insert(x),
            2 => trie.remove(x),
            3 => writeln!(io.writer, "{}", trie.max_xor(x)).unwrap(),
            _ => unreachable!(),
        }
    }
}

struct Trie {
    count: Cell<u32>,
    next: [RefCell<Option<Box<Trie>>>; 2],
}

impl Trie {
    #[inline]
    fn insert(&self, val: u32) {
        self.update_with(val.reverse_bits(), 0, |val| val + 1)
    }

    #[inline]
    fn remove(&self, val: u32) {
        self.update_with(val.reverse_bits(), 0, |val| val - 1)
    }

    #[inline]
    fn update_with<F>(&self, val: u32, index: usize, updater: F)
    where
        F: Fn(u32) -> u32,
    {
        self.count.set(updater(self.count.get()));
        if index >= size_of::<u32>() * 8 {
            return;
        }
        let bit = if (val & (1 << index)) == 0 { 0 } else { 1 };
        self.next[bit]
            .borrow_mut()
            .get_or_insert_with(|| Box::new(Trie::default()))
            .update_with(val, index + 1, updater)
    }

    #[inline]
    fn max_xor(&self, val: u32) -> u32 {
        self.max_xor_inner(val.reverse_bits(), 0, 0).reverse_bits()
    }

    #[inline]
    fn max_xor_inner(&self, val: u32, index: usize, acc: u32) -> u32 {
        if index >= size_of::<u32>() * 8 {
            return acc;
        }
        let (desired, secondary) = match val & (1 << index) {
            0 => (1, 0),
            _ => (0, 1),
        };
        if let Some(node) = &*self.next[desired].borrow_mut() {
            if node.count.get() > 0 {
                return node.max_xor_inner(val, index + 1, acc | (1 << index));
            }
        }
        if let Some(node) = &*self.next[secondary].borrow_mut() {
            if node.count.get() > 0 {
                return node.max_xor_inner(val, index + 1, acc);
            }
        }
        unreachable!()
    }
}

impl Default for Trie {
    fn default() -> Self {
        Self {
            count: Cell::new(0),
            next: [RefCell::new(None), RefCell::new(None)],
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

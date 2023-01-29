use std::ops::{Add, AddAssign, Sub};

pub struct SegTree<'g, T, F>
where
    F: Fn(T, T) -> T,
{
    origin_count: usize,
    tree: Vec<T>,
    reduce: &'g F,
}

impl<'g, T, F> SegTree<'g, T, F>
where
    T: Add + AddAssign + Sub<Output = T> + PartialOrd + Copy + Default,
    F: Fn(T, T) -> T,
{
    pub fn new(origin_count: usize, reduce: &'g F) -> Self {
        let tree_height = (origin_count as f64).log2().ceil() as usize;
        let vec_size = 1 << (tree_height + 1);
        Self {
            origin_count,
            tree: vec![T::default(); vec_size],
            reduce,
        }
    }

    pub fn from(origin: &Vec<T>, reduce: &'g F) -> Self {
        let mut result = Self::new(origin.len(), reduce);
        result.initialize(1, 0, result.origin_count - 1, origin);
        result
    }

    pub fn update<'l, G>(&mut self, pos: usize, updater: &'l G)
    where
        G: Fn(&mut T),
    {
        self.update_inner(1, pos, 0, self.origin_count - 1, updater)
    }

    pub fn query(&self, start: usize, end: usize) -> T {
        self.query_inner(1, start, end, 0, self.origin_count - 1)
    }

    fn initialize(&mut self, index: usize, start: usize, end: usize, origin: &[T]) {
        if start == end {
            self.tree[index] = origin[start];
        } else {
            let mid = (start + end) / 2;
            self.initialize(index * 2, start, mid, origin);
            self.initialize(index * 2 + 1, mid + 1, end, origin);
            self.tree[index] = (self.reduce)(self.tree[index * 2], self.tree[index * 2 + 1]);
        }
    }

    fn query_inner(
        &self,
        index: usize,
        req_start: usize,
        req_end: usize,
        tree_start: usize,
        tree_end: usize,
    ) -> T {
        let req_start = req_start.max(tree_start);
        let req_end = req_end.min(tree_end);
        if req_start == tree_start && tree_end == req_end {
            return self.tree[index];
        }

        let tree_mid = (tree_start + tree_end) / 2;
        let left = !(tree_mid < req_start);
        let right = !(req_end <= tree_mid);

        if left && right {
            (self.reduce)(
                self.query_inner(index * 2, req_start, req_end, tree_start, tree_mid),
                self.query_inner(index * 2 + 1, req_start, req_end, tree_mid + 1, tree_end),
            )
        } else if left {
            self.query_inner(index * 2, req_start, req_end, tree_start, tree_mid)
        } else {
            self.query_inner(index * 2 + 1, req_start, req_end, tree_mid + 1, tree_end)
        }
    }

    fn update_inner<'l, G>(
        &mut self,
        index: usize,
        req_pos: usize,
        tree_start: usize,
        tree_end: usize,
        updater: &'l G,
    ) where
        G: Fn(&mut T),
    {
        if tree_start == req_pos && tree_end == req_pos {
            (updater)(&mut self.tree[index]);
        } else if tree_start <= req_pos && req_pos <= tree_end {
            let tree_mid = (tree_start + tree_end) / 2;
            self.update_inner(index * 2, req_pos, tree_start, tree_mid, updater);
            self.update_inner(index * 2 + 1, req_pos, tree_mid + 1, tree_end, updater);
            self.tree[index] = (self.reduce)(self.tree[index * 2], self.tree[index * 2 + 1]);
        }
    }
}

use std::io::{BufRead, BufWriter, Write};

fn main() {
    let stdin = std::io::stdin();
    let stdout = std::io::stdout();
    let io = &mut IO::new(stdin.lock(), stdout.lock());

    let n = io.usize();
    let arr = io.usizes(n);
    let mut comp = arr.clone();
    comp.sort();
    comp.dedup();

    let mut tree = SegTree::new(arr.len()+1, &|a: usize, b| a + b);
    writeln!(
        io.writer,
        "{}",
        arr.iter()
            .map(|v| {
                let v = comp.partition_point(|x| x < v);
                let count = tree.query(v+1, arr.len() as usize);
                tree.update(v, &|x| *x += 1);
                count
            })
            .sum::<usize>()
    )
    .unwrap();
}

// Modified EbTech's Scanner
pub struct IO<R, W: Write> {
    reader: R,
    writer: BufWriter<W>,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
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
io_shortcut!(i64, i64, i64s);
io_shortcut!(u64, u64, u64s);
io_shortcut!(usize, usize, usizes);
io_shortcut!(f64, f64, f64s);
io_shortcut!(String, string, strings);

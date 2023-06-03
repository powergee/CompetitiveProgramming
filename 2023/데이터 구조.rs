use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    for _ in 0..n {
        let (t, x) = (io.usize(), io.usize());
        if t == 1 {
            push(x);
        } else {
            writeln!(io.writer, "{}", pop(x)).unwrap();
        }
    }
}

static mut NODE: [usize; 4194304] = [0; 4194304];
const MAX: usize = 2000001;

fn push(val: usize) {
    push_inner(val, 1, 0, MAX - 1);
}

fn pop(pos: usize) -> usize {
    pop_inner(pos, 1, 0, MAX - 1)
}

fn push_inner(val: usize, node_index: usize, tree_start: usize, tree_end: usize) {
    debug_assert!(tree_start <= val && val <= tree_end);
    unsafe { NODE[node_index] += 1 };
    if tree_start == val && val == tree_end {
        return;
    }
    let tree_mid = (tree_start + tree_end) / 2;
    if val <= tree_mid {
        push_inner(val, node_index * 2, tree_start, tree_mid);
    } else {
        push_inner(val, node_index * 2 + 1, tree_mid + 1, tree_end);
    }
}

fn pop_inner(pos: usize, node_index: usize, tree_start: usize, tree_end: usize) -> usize {
    let node = unsafe { &mut NODE };
    debug_assert!(1 <= pos && pos <= node[node_index]);
    node[node_index] -= 1;
    if tree_start == tree_end {
        return tree_start;
    }
    let tree_mid = (tree_start + tree_end) / 2;
    if pos <= node[node_index * 2] {
        pop_inner(pos, node_index * 2, tree_start, tree_mid)
    } else {
        pop_inner(
            pos - node[node_index * 2],
            node_index * 2 + 1,
            tree_mid + 1,
            tree_end,
        )
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

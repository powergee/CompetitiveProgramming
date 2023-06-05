use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();

    for t in 1.. {
        let (n, m) = (io.usize(), io.usize());
        if n == 0 {
            break;
        }
        write!(io.writer, "Case {t}: ").unwrap();

        let mut dsu = DisjointSet::new(n + 1);
        for _ in 0..m {
            let (u, v) = (io.usize(), io.usize());
            dsu.union_nodes(u, v);
        }

        let mut root = Vec::with_capacity(n);
        for v in 1..=n {
            root.push(dsu.find_parent(v));
        }
        root.sort_unstable();
        root.dedup();

        let trees = root.into_iter().filter(|r| dsu.is_tree(*r)).count();
        match trees {
            0 => writeln!(io.writer, "No trees.").unwrap(),
            1 => writeln!(io.writer, "There is one tree.").unwrap(),
            _ => writeln!(io.writer, "A forest of {trees} trees.").unwrap(),
        }
    }
}

struct DisjointSet {
    parent: Vec<usize>,
    is_graph: Vec<bool>,
}

impl DisjointSet {
    fn new(size: usize) -> DisjointSet {
        let parent = (0..size).collect();
        let is_graph = vec![false; size];
        DisjointSet { parent, is_graph }
    }

    fn find_parent(&mut self, x: usize) -> usize {
        let p = self.parent.get(x).expect("DisjointSet: x is out of range");
        if *p == x {
            x
        } else {
            let new_parent = self.find_parent(p.clone());
            self.parent[x] = new_parent;
            new_parent
        }
    }

    fn is_tree(&self, x: usize) -> bool {
        !self.is_graph[x]
    }

    fn union_nodes(&mut self, x: usize, y: usize) {
        let x_par = self.find_parent(x);
        let y_par = self.find_parent(y);
        self.parent[x_par] = y_par;
        if x_par == y_par {
            self.is_graph[x_par] = true;
        } else {
            self.is_graph[y_par] = self.is_graph[x_par] || self.is_graph[y_par];
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

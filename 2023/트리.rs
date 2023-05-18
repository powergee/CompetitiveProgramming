use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

enum Query {
    Remove(usize),
    IsConnected(usize, usize),
}

fn main() {
    let mut io = IO::stdio();

    let (n, mut q) = (io.usize(), io.usize());
    q += n - 1;
    let mut parent = vec![0; n + 1];
    for child in 2..=n {
        parent[child] = io.usize();
    }

    let mut removed = vec![false; n + 1];
    let queries = (0..q)
        .map(|_| {
            let t = io.usize();
            if t == 0 {
                let child = io.usize();
                removed[child] = true;
                Query::Remove(child)
            } else {
                Query::IsConnected(io.usize(), io.usize())
            }
        })
        .collect::<Vec<_>>();

    let mut dsu = DisjointSet::new(n + 1);
    for child in 1..=n {
        if !removed[child] {
            dsu.union_nodes(child, parent[child]);
        }
    }

    let mut answer = Vec::with_capacity(q);
    for query in queries.iter().rev() {
        match query {
            Query::Remove(child) => {
                dsu.union_nodes(*child, parent[*child]);
            }
            Query::IsConnected(u, v) => {
                answer.push(dsu.find_parent(*u) == dsu.find_parent(*v));
            }
        }
    }
    for ans in answer.iter().rev() {
        writeln!(io.writer, "{}", if *ans { "YES" } else { "NO" }).unwrap();
    }
}

struct DisjointSet {
    parent: Vec<usize>,
}

impl DisjointSet {
    fn new(size: usize) -> DisjointSet {
        let parent = (0..size).collect();
        DisjointSet { parent }
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

    fn union_nodes(&mut self, x: usize, y: usize) {
        let x_par = self.find_parent(x);
        let y_par = self.find_parent(y);
        self.parent[x_par] = y_par;
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

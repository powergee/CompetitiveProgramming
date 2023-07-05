use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let (n, m) = (io.usize(), io.usize());

    let mut dsu = DisjointSet::new(n + 1);
    for _ in 0..m {
        let (u, v) = (io.usize(), io.usize());
        if u > v {
            for i in v..u {
                dsu.union_nodes(i, i + 1);
            }
        }
    }

    let mut sizes = vec![];
    let mut last_parent = 0;
    for x in 1..n + 1 {
        let p = dsu.find_parent(x);
        if last_parent != p {
            last_parent = p;
            sizes.push(dsu.size_of_set(x));
        }
    }

    let mut answer = 1;
    for div in 1..n + 1 {
        if n % div != 0 {
            continue;
        }
        let mut need = div;
        let mut success = true;
        for &s in &sizes {
            match s.cmp(&need) {
                std::cmp::Ordering::Less => need -= s,
                std::cmp::Ordering::Equal => need = div,
                std::cmp::Ordering::Greater => {
                    success = false;
                    break;
                }
            }
        }
        if success && need == div {
            answer = n / div;
            break;
        }
    }

    writeln!(io.writer, "{answer}").unwrap();
}

struct DisjointSet {
    parent: Vec<usize>,
    size: Vec<usize>,
}

impl DisjointSet {
    fn new(size: usize) -> DisjointSet {
        let parent = (0..size).collect();
        let size = vec![1; size];
        DisjointSet { parent, size }
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
        if x_par != y_par {
            self.size[y_par] += self.size[x_par];
            self.parent[x_par] = y_par;
        }
    }

    fn size_of_set(&mut self, x: usize) -> usize {
        let p = self.find_parent(x);
        self.size[p]
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

macro_rules! io_shortcut {(
    $(($type:ident, $types:ident))*
) => (
    $(
        impl<R: BufRead, W: Write> IO<R, W> {
            #[inline]
            #[allow(unused)]
            fn $type(&mut self) -> $type {
                self.next()
            }
            #[inline]
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
    (usize, usizes)
}

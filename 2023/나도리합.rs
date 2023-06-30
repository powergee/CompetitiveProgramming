use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let (n, q) = (io.usize(), io.usize());
    let power = io.usizes(n);
    let mut dsu = DisjointSet::new(power);
    for _ in 0..q {
        let (a, b) = (io.usize() - 1, io.usize() - 1);
        writeln!(io.writer, "{}", dsu.union_nodes(a, b)).unwrap();
    }
}

struct DisjointSet {
    parent: Vec<usize>,
    power_sum: Vec<usize>,
    power_conv: Vec<usize>,
}

impl DisjointSet {
    fn new(power: Vec<usize>) -> DisjointSet {
        let parent = (0..power.len()).collect();
        let power_conv = vec![0; power.len()];
        DisjointSet {
            parent,
            power_sum: power,
            power_conv,
        }
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

    fn union_nodes(&mut self, x: usize, y: usize) -> usize {
        let x_par = self.find_parent(x);
        let y_par = self.find_parent(y);
        self.parent[x_par] = y_par;
        if x_par != y_par {
            let sx = self.power_sum[x_par];
            let sy = self.power_sum[y_par];
            let cx = self.power_conv[x_par];
            let cy = self.power_conv[y_par];
            self.power_sum[y_par] = sx + sy;
            self.power_conv[y_par] = cx + cy + sx * sy;
        }
        self.power_conv[y_par]
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

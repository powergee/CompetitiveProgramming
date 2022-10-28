use std::{io::{BufRead, BufWriter, Write}};

const SPARSE_MAX:usize = 18;
const INF:u64 = 1000000000000000001;

fn main() {
    let stdin = std::io::stdin();
    let stdout = std::io::stdout();
    let io = &mut IO::new(stdin.lock(), stdout.lock());

    let mut parent = vec![vec![0; SPARSE_MAX]; 150001];
    let mut dist = vec![vec![0; SPARSE_MAX]; 150001];
    dist[0].fill(INF);

    let q = io.usize();
    let mut last_answer = 0;
    let mut m = 1;
    for _ in 0..q {
        let query = io.string();
        if query == "ad-hoc" {
            let (k, l) = (io.usize(), io.u64());
            let (par, curr) = ((k+last_answer) % m, m);

            parent[curr][0] = par;
            for e in 1..SPARSE_MAX {
                parent[curr][e] = parent[parent[curr][e-1]][e-1];
            }
            dist[curr][0] = l;
            for e in 1..SPARSE_MAX {
                dist[curr][e] = dist[curr][e-1] + dist[parent[curr][e-1]][e-1];
            }
            m += 1;
        } else {
            let (mut curr, mut l) = (io.usize(), io.u64());
            loop {
                if curr == 0 || l < dist[curr][0] {
                    break;
                }
                for e in (0..SPARSE_MAX).rev() {
                    if dist[curr][e] <= l {
                        l -= dist[curr][e];
                        curr = parent[curr][e];
                        break;
                    }
                }
            }
            writeln!(io.writer, "{curr}").ok();
            last_answer = curr;
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

impl<R: BufRead, W: Write> IO<R, W> {
    pub fn new(reader: R, writer: W) -> Self {
        Self {
            reader,
            writer: BufWriter::new(writer),
            buf_str: String::new(),
            buf_iter: "".split_whitespace()
        }
    }

    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader.read_line(&mut self.buf_str).expect("Failed read");
            self.buf_iter = unsafe { std::mem::transmute(self.buf_str.split_whitespace()) };
        }
    }
}

macro_rules! io_shortcut {
    ($scan_type:ident, $single_ident:ident, $multi_ident:ident) => {
        impl<R: BufRead, W: Write> IO<R, W> {
            #[allow(unused)]
            fn $single_ident(&mut self) -> $scan_type {
                self.next()
            }
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
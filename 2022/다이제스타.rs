use std::io::{BufRead, BufWriter, Write};

const MAX: usize = 10000001;
const INF: usize = usize::MAX/2;

fn main() {
    let stdin = std::io::stdin();
    let stdout = std::io::stdout();
    let io = &mut IO::new(stdin.lock(), stdout.lock());

    let (n, m) = (io.usize(), io.usize());
    let mut edges_by_cost = vec![vec![]; MAX];

    for _ in 0..m {
        let (u, v, c) = (io.usize(), io.usize(), io.usize());
        edges_by_cost[c].push((u, v));
    }
    let (s, e) = (io.usize(), io.usize());

    let mut dist = vec![INF; n+1];
    let mut next = vec![INF; n+1];
    dist[s] = 0;
    for (cost, edges) in edges_by_cost.iter().enumerate() {
        for &(u, v) in edges {
            next[u] = next[u].min(dist[u].min(dist[v] + cost));
            next[v] = next[v].min(dist[v].min(dist[u] + cost));
        }
        for &(u, v) in edges {
            if next[u] != INF {
                dist[u] = next[u];
                next[u] = INF;
            }
            if next[v] != INF {
                dist[v] = next[v];
                next[v] = INF;
            }
        }
    }

    if dist[e] == INF {
        writeln!(io.writer, "DIGESTA").unwrap();
    } else {
        writeln!(io.writer, "{}", dist[e]).unwrap();
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

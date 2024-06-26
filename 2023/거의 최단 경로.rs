use std::{
    cmp::Reverse,
    collections::BinaryHeap,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    loop {
        let (n, m) = (io.usize(), io.usize());
        if n == 0 {
            break;
        }

        let (s, d) = (io.usize(), io.usize());
        let edges = (0..m)
            .map(|_| (io.usize(), io.usize(), io.usize()))
            .collect::<Vec<_>>();

        let s_dist = get_dist(s, n, &edges, false);
        let d_dist = get_dist(d, n, &edges, true);
        let mut unused = vec![];
        for &(u, v, w) in &edges {
            if s_dist[d] < s_dist[u] + w + d_dist[v] {
                unused.push((u, v, w));
            }
        }

        let unused_dist = get_dist(s, n, &unused, false);
        writeln!(
            io.writer,
            "{}",
            if unused_dist[d] == usize::MAX / 3 {
                -1
            } else {
                unused_dist[d] as i64
            }
        )
        .unwrap();
    }
}

fn get_dist(
    start: usize,
    n: usize,
    edges: &Vec<(usize, usize, usize)>,
    rev_edge: bool,
) -> Vec<usize> {
    let mut graph = vec![vec![]; n];
    for &(u, v, w) in edges {
        if rev_edge {
            graph[v].push((u, w));
        } else {
            graph[u].push((v, w));
        }
    }
    let mut dist = vec![usize::MAX / 3; n];
    dist[start] = 0;
    let mut q = BinaryHeap::new();
    q.push((Reverse(0), start));

    while let Some((Reverse(curr_dist), curr)) = q.pop() {
        if dist[curr] != curr_dist {
            continue;
        }
        for &(next, w) in &graph[curr] {
            let next_dist = curr_dist + w;
            if dist[next] > next_dist {
                dist[next] = next_dist;
                q.push((Reverse(next_dist), next));
            }
        }
    }

    dist
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
io_shortcut!(i64, i64, i64s);

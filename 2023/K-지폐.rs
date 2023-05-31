use std::{
    cmp::Reverse,
    collections::BinaryHeap,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let (n, m, k) = (io.usize(), io.usize(), io.usize());
    let (s, t) = (io.usize(), io.usize());

    let mut graph = vec![vec![]; n + 1];
    for _ in 0..m {
        let (u, v, w) = (io.usize(), io.usize(), io.usize());
        graph[u].push((v, w));
    }

    let mut dist = vec![vec![usize::MAX / 2; k]; n + 1];
    dist[s][0] = 0;
    let mut q = BinaryHeap::new();
    q.push((Reverse(0), s));

    while let Some((Reverse(curr_dist), curr)) = q.pop() {
        if curr_dist != dist[curr][curr_dist % k] {
            continue;
        }
        for &(next, w) in &graph[curr] {
            let next_dist = curr_dist + w;
            if next_dist < dist[next][next_dist % k] {
                dist[next][next_dist % k] = next_dist;
                q.push((Reverse(next_dist), next));
            }
        }
    }

    if dist[t][0] == usize::MAX / 2 {
        writeln!(io.writer, "IMPOSSIBLE").unwrap();
    } else {
        writeln!(io.writer, "{}", dist[t][0]).unwrap();
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
io_shortcut!(i64, i64, i64s);

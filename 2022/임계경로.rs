use std::{io::BufRead, collections::VecDeque};

fn main() {
    let stdin = std::io::stdin();
    let scan = &mut Scanner::new(stdin.lock());

    let n = scan.usize();
    let m = scan.usize();
    let mut graph = vec![vec![]; n+1];
    let mut indegree = vec![0; n+1];
    for _ in 0..m {
        let (u, v, c) = (scan.usize(), scan.usize(), scan.usize());
        graph[u].push((v, c));
        indegree[v] += 1;
    }
    let (src, _) = (scan.usize(), scan.usize());

    let mut topology = vec![];
    let mut q = VecDeque::new();
    q.push_back(src);

    while let Some(curr) = q.pop_front() {
        topology.push(curr);
        for &(next, _) in &graph[curr] {
            indegree[next] -= 1;
            if indegree[next] == 0 {
                q.push_back(next);
            }
        }
    }

    let mut dist = vec![0; n+1];
    for &curr in topology.iter().rev() {
        for &(next, cost) in &graph[curr] {
            dist[curr] = dist[curr].max(dist[next] + cost);
        }
    }

    let mut road_cnt = 0;
    let mut q = VecDeque::new();
    let mut visited = vec![false; n+1];

    q.push_back(src);
    visited[src] = true;

    while let Some(curr) = q.pop_front() {
        for &(next, cost) in &graph[curr] {
            if dist[curr] == dist[next] + cost {
                road_cnt += 1;
                if !visited[next] {
                    q.push_back(next);
                    visited[next] = true;
                }
            }
        }
    }

    println!("{}\n{}", dist[src], road_cnt);
}

// From EbTech
pub struct Scanner<B> {
    reader: B,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
}

impl<B: BufRead> Scanner<B> {
    pub fn new(reader: B) -> Self {
        Self {
            reader,
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


macro_rules! scanner_shortcut {
    ($scan_type:ident, $single_scan_ident:ident, $multi_scan_ident:ident) => {
        impl<B: BufRead> Scanner<B> {
            #[allow(unused)]
            fn $single_scan_ident(&mut self) -> $scan_type {
                self.next()
            }
            #[allow(unused)]
            fn $multi_scan_ident(&mut self, n: usize) -> Vec<$scan_type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    };
}
scanner_shortcut!(usize, usize, usizes);
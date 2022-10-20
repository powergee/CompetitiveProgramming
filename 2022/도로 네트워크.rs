use std::{io::{BufRead, BufWriter, Write}, collections::VecDeque};

const LCA_MAX:usize = 18;

fn main() {
    let stdin = std::io::stdin();
    let scan = &mut Scanner::new(stdin.lock());

    let n = scan.usize();
    let mut graph = vec![vec![]; n+1];
    for _ in 0..n-1 {
        let (u, v, c) = (scan.usize(), scan.usize(), scan.usize());
        graph[u].push((v, c));
        graph[v].push((u, c));
    }

    let mut parent = vec![vec![0; LCA_MAX]; n+1];
    let mut depth = vec![0; n+1];
    let mut min = vec![vec![usize::MAX; LCA_MAX]; n+1];
    let mut max = vec![vec![usize::MIN; LCA_MAX]; n+1];
    let mut q = VecDeque::new();
    q.push_back(1);
    depth[1] = 0;
    parent[1].fill(1);
    
    while let Some(curr) = q.pop_front() {
        for &(next, cost) in &graph[curr] {
            if parent[next][0] == 0 {
                parent[next][0] = curr;
                depth[next] = depth[curr]+1;
                min[next][0] = cost;
                max[next][0] = cost;

                for e in 1..LCA_MAX {
                    let upper = parent[next][e-1];
                    parent[next][e] = parent[upper][e-1];
                    min[next][e] = min[next][e-1].min(min[upper][e-1]);
                    max[next][e] = max[next][e-1].max(max[upper][e-1]);
                }
                q.push_back(next);
            }
        }
    }

    let reduce_between = |u: usize, v: usize, init: usize, reduce: &dyn Fn(usize, usize, usize) -> usize| {
        let (mut lower, mut upper) = if depth[u] > depth[v] { (u, v) } else { (v, u) };
        let mut result = init;

        for e in (0..LCA_MAX).rev() {
            let lower_parent = parent[lower][e];
            if depth[lower_parent] >= depth[upper] {
                result = reduce(result, lower, e);
                lower = lower_parent;
            }
        }
        
        for e in (0..LCA_MAX).rev() {
            let lower_parent = parent[lower][e];
            let upper_parent = parent[upper][e];
            if lower_parent != upper_parent {
                result = reduce(result, lower, e);
                result = reduce(result, upper, e);
                (lower, upper) = (lower_parent, upper_parent);
            } 
        }
        if lower != upper {
            result = reduce(result, lower, 0);
            result = reduce(result, upper, 0);
        }
        result
    };

    let reduce_min = |result: usize, target: usize, e: usize| {
        result.min(min[target][e])
    };
    let reduce_max = |result: usize, target: usize, e: usize| {
        result.max(max[target][e])
    };

    let q = scan.usize();
    let stdout = std::io::stdout();
    let mut writer = BufWriter::new(stdout.lock());
    for _ in 0..q {
        let (u, v) = (scan.usize(), scan.usize());
        
        let min = reduce_between(u, v, usize::MAX, &reduce_min);
        let max = reduce_between(u, v, usize::MIN, &reduce_max);
        writeln!(writer, "{min} {max}").ok();
    }
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
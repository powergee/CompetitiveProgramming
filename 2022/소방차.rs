use std::{collections::BinaryHeap, cmp::Reverse};

fn main() {
    let scan = &mut Scanner::default();
    let n = scan.usize();
    let charge = [0].iter().chain(scan.i64s(n).iter()).copied().collect::<Vec<_>>();
    let m = scan.usize();
    let mut graph = vec![vec![]; n+1];
    
    for _ in 0..m {
        let (u, v, c) = (scan.usize(), scan.usize(), scan.i64());
        graph[u].push((v, c));
        graph[v].push((u, c));
    }

    let (s, t) = (scan.usize(), scan.usize());

    let mut dist = vec![(i64::MAX, Reverse(0)); n+1];
    let mut q = BinaryHeap::new();
    dist[s] = (0, Reverse(charge[s]));
    q.push((Reverse(dist[s]), s));
    
    while let Some((Reverse(curr_dist), curr)) = q.pop() {
        if curr_dist > dist[curr] {
            continue;
        }
        for (next, cost) in &graph[curr] {
            let Reverse(curr_charge) = dist[curr].1;
            let new_dist = (dist[curr].0 + cost, Reverse(curr_charge + charge[*next]));
            if new_dist < dist[*next] {
                dist[*next] = new_dist;
                q.push((Reverse(dist[*next]), *next));
            }
        }
    }

    let (final_dist, Reverse(final_charge)) = dist[t];
    if final_dist == i64::MAX {
        println!("-1");
    } else {
        println!("{} {}", final_dist, final_charge);
    }
}

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            std::io::stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

macro_rules! scanner_shortcut {
    ($scan_type:ident, $single_scan_ident:ident, $multi_scan_ident:ident) => {
        impl Scanner {
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
scanner_shortcut!(i32, i32, i32s);
scanner_shortcut!(i64, i64, i64s);
scanner_shortcut!(isize, isize, isizes);
scanner_shortcut!(u32, u32, u32s);
scanner_shortcut!(u64, u64, u64s);
scanner_shortcut!(usize, usize, usizes);
scanner_shortcut!(f64, f64, f64s);
scanner_shortcut!(String, string, strings);
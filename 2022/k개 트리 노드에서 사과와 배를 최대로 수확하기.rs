use std::collections::BTreeSet;
use std::io::BufRead;

fn main() {
    let stdin = std::io::stdin();
    let scan = &mut Scanner::new(stdin.lock());
    let (n, k) = (scan.usize(), scan.usize());

    let mut graph = vec![vec![]; n];
    for _ in 0..n-1 {
        let (u, v) = (scan.usize(), scan.usize());
        graph[u].push(v);
    }
    let fruit = scan.usizes(n);
    let mut prev = vec![];
    let mut paths = vec![vec![]; n];
    find_path(&graph, 0, &mut prev, &mut paths);

    let mut answer = (0, 0, 0);
    for mask in 0..(1<<n) {
        let mut selected = BTreeSet::new();
        for e in 0..n {
            if (mask&(1<<e)) > 0 {
                for v in &paths[e] {
                    selected.insert(v.clone());
                }
            }
        }
        let (apples, pears): (Vec<usize>, Vec<usize>) = selected.iter()
            .filter(|i| fruit[**i] > 0)
            .partition(|i| fruit[**i] == 1);
        
        if selected.len() <= k {
            answer = answer.max((apples.len() * pears.len(), apples.len(), pears.len()));
        }
    }

    println!("{} {}", answer.1, answer.2);
}

fn find_path(graph: &Vec<Vec<usize>>, start: usize, prev: &mut Vec<usize>, result: &mut Vec<Vec<usize>>) {
    prev.push(start);
    result[start] = prev.clone();
    for next in &graph[start] {
        find_path(graph, *next, prev, result);
    }
    prev.pop();
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
scanner_shortcut!(i32, i32, i32s);
scanner_shortcut!(i64, i64, i64s);
scanner_shortcut!(isize, isize, isizes);
scanner_shortcut!(u32, u32, u32s);
scanner_shortcut!(u64, u64, u64s);
scanner_shortcut!(usize, usize, usizes);
scanner_shortcut!(f64, f64, f64s);
scanner_shortcut!(String, string, strings);
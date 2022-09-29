use std::{cell::RefCell, io::BufWriter};
use std::io::Write;

fn main() {
    let scan = &mut Scanner::default();
    let tree = Tree::new(scan);
    tree.count_colors(1);
    tree.count_path(1);

    let q = scan.usize();
    let path_count = tree.path_count.borrow();
    let mut writer = BufWriter::new(std::io::stdout());
    for _ in 0..q {
        let u = scan.usize();
        writeln!(writer, "{}", path_count[u]).unwrap();
    }
}

#[derive(Default)]
struct Tree {
    adj: Vec<Vec<usize>>,
    colors: Vec<usize>,
    total_1st: u64,
    total_2nd: u64,
    total_colors: RefCell<Vec<(u64, u64)>>,
    parent: RefCell<Vec<usize>>,
    path_count: RefCell<Vec<u64>>,
}

impl Tree {
    fn new(scan: &mut Scanner) -> Tree {
        let n = scan.usize();
        let colors = scan.usizes(n, 1);
        let mut adj = vec![vec![]; n+1];
        for _ in 0..n-1 {
            let (u, v) = (scan.usize(), scan.usize());
            adj[u].push(v);
            adj[v].push(u);
        }
        let sum: usize = colors.iter().sum();
        Tree {
            adj,
            colors,
            total_1st: (n-sum) as u64,
            total_2nd: sum as u64,
            total_colors: vec![(0, 0); n+1].into(),
            parent: vec![0; n+1].into(),
            path_count: vec![0; n+1].into()
        }
    }

    fn count_colors(&self, start: usize) {
        if self.colors[start] == 0 {
            self.total_colors.borrow_mut()[start].0 += 1;
        } else {
            self.total_colors.borrow_mut()[start].1 += 1;
        }
        for &next in &self.adj[start] {
            if self.parent.borrow()[start] == next {
                continue;
            }
            self.parent.borrow_mut()[next] = start;
            self.count_colors(next);

            let mut total_colors = self.total_colors.borrow_mut();
            total_colors[start].0 += total_colors[next].0;
            total_colors[start].1 += total_colors[next].1;
        }
    }

    fn count_path(&self, center: usize) {
        let subtree_colors = self.total_colors.borrow()[center];
        let parent_colors = (self.total_1st - subtree_colors.0, self.total_2nd - subtree_colors.1);

        let neighbors = self.adj[center]
            .iter()
            .filter(|next| self.parent.borrow()[center] != **next)
            .map(|next| self.total_colors.borrow()[*next])
            .chain([parent_colors].iter().copied())
            .collect::<Vec<_>>();

        let answer = neighbors
            .iter()
            .fold(0, |paths, (r, b)| paths + r*(self.total_2nd-(self.colors[center] as u64)-b));
        self.path_count.borrow_mut()[center] = answer;

        for &next in &self.adj[center] {
            if self.parent.borrow()[center] == next {
                continue;
            }
            self.count_path(next);
        }
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
            fn $multi_scan_ident(&mut self, n: usize, padding: usize) -> Vec<$scan_type> {
                std::iter::repeat(Default::default())
                    .take(padding)
                    .chain((0..n).map(|_| self.next()))
                    .collect()
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
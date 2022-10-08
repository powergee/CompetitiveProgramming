use core::cell::RefCell;

fn main() {
    let scan = &mut Scanner::default();
    let tree = Tree::new(scan);
    println!("{}", tree.get_min_cost(0, 0));
}

#[derive(Default)]
struct Tree {
    graph: Vec<Vec<usize>>,
    cost: Vec<(i64, i64)>,
    dp: RefCell<Vec<Vec<i64>>>
}

impl Tree {
    fn new(scan: &mut Scanner) -> Tree {
        let n = scan.usize();
        let mut graph = vec![vec![]; n];
        for _ in 0..(n-1) {
            let (u, v) = (scan.usize(), scan.usize());
            graph[u].push(v);
        }
        let cost = (0..n).map(|_| (scan.i64(), scan.i64())).collect::<Vec<_>>();

        Tree {
            graph, cost,
            dp: vec![vec![-1; 2]; n].into()
        }
    }

    fn get_min_cost(&self, start: usize, parent_black: usize) -> i64 {
        if -1 != self.dp.borrow()[start][parent_black] {
            return self.dp.borrow()[start][parent_black];
        }

        // 현재 노드를 흰 색으로 칠하는 경우
        let mut result = self.cost[start].0 + {
            let mut total = 0;
            for next in &self.graph[start] {
                total += self.get_min_cost(*next, 0);
            }
            total
        };
        // (부모 노드가 검은색이 아닐 경우에만 가능)
        // 현재 노드를 검은색으로 칠하는 경우
        if parent_black == 0 {
            result = result.min(self.cost[start].1 + {
                let mut total = 0;
                for next in &self.graph[start] {
                    total += self.get_min_cost(*next, 1);
                }
                total
            });
        }
        self.dp.borrow_mut()[start][parent_black] = result;
        return result;
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
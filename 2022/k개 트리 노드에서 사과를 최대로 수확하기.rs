use std::collections::VecDeque;

fn main() {
    let scan = &mut Scanner::default();
    let n = scan.usize();
    let k = scan.usize();
    let mut graph = vec![vec![]; n];
    for _ in 0..(n-1) {
        let (u, v) = (scan.usize(), scan.usize());
        graph[u].push(v);
    }
    let apple = scan.usizes(n);

    let pop_count = |v| {
        let mut result = 0;
        for i in 0..n {
            if (v&(1<<i)) > 0 {
                result += 1;
            }
        }
        return result;
    };

    let mut answer = 0;
    for mask in 0..(1<<n) {
        if pop_count(mask) == k && is_connected(&graph, mask) {
            let mut count = 0;
            for i in 0..n {
                if mask&(1<<i) > 0 {
                    count += apple[i];
                }
            }
            answer = answer.max(count);
        }
    }
    println!("{answer}");
}

fn is_connected(graph: &Vec<Vec<usize>>, mask: usize) -> bool {
    let mut q = VecDeque::new();
    let mut visited = 1;
    q.push_back(0);
    while let Some(curr) = q.pop_front() {
        for next in &graph[curr] {
            if (mask&(1<<*next)) > 0 && (visited&(1<<*next)) == 0 {
                visited |= 1<<*next;
                q.push_back(*next);
            }
        }
    }
    mask == visited
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
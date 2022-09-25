use std::convert::TryInto;

fn main() {
    let scan = &mut Scanner::default();
    let n = scan.usize();
    let m = scan.usize();

    let xs: Vec<_> = (0..n).map(|_| scan.usize()).collect();
    let ys: Vec<_> = (0..n).map(|_| scan.usize()).collect();
    let bridges: Vec<_> = (0..m).map(|_| (scan.usize(), scan.usize(), scan.u64())).collect();

    let mut answer = std::u64::MAX;
    for mask in 0..4 {
        let mut edges = bridges.clone();
        if mask & 1 > 0 {
            for (i, x) in xs.iter().enumerate() {
                edges.push((n+1, i+1, x.clone().try_into().unwrap()));
            }
        }
        if mask & 2 > 0 {
            for (i, y) in ys.iter().enumerate() {
                edges.push((n+2, i+1, y.clone().try_into().unwrap()));
            }
        }

        edges.sort_by(|a, b| a.2.cmp(&b.2));
        let mut total = 0;
        let mut dsu = DisjointSet::new(n+3);
        for (u, v, cost) in edges {
            if dsu.find_parent(u) != dsu.find_parent(v) {
                dsu.union_nodes(u, v);
                total += cost;
            }
        }
        
        let mut connected = true;
        for v in 1..=n {
            if dsu.find_parent(1) != dsu.find_parent(v) {
                connected = false;
                break;
            }
        }

        if connected {
            answer = std::cmp::min(answer, total);
        }
    }

    println!("{}", answer);
}

struct DisjointSet {
    parent: Vec<usize>
}

impl DisjointSet {
    fn new(size: usize) -> DisjointSet {
        let parent = (0..size).collect();
        DisjointSet { parent }
    }

    fn find_parent(&mut self, x: usize) -> usize {
        let p = self.parent.get(x).expect("DisjointSet: x is out of range");
        if *p == x {
            x
        } else {
            let new_parent = self.find_parent(p.clone());
            self.parent[x] = new_parent;
            new_parent 
        }
    }

    fn union_nodes(&mut self, x: usize, y: usize) {
        let x_par = self.find_parent(x);
        let y_par = self.find_parent(y);
        self.parent[x_par] = y_par;
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
    ($scan_type:ident) => {
        impl Scanner {
            #[allow(unused)]
            fn $scan_type(&mut self) -> $scan_type {
                self.next()
            }
        }
    };
}
scanner_shortcut!(i32);
scanner_shortcut!(i64);
scanner_shortcut!(isize);
scanner_shortcut!(u32);
scanner_shortcut!(u64);
scanner_shortcut!(usize);

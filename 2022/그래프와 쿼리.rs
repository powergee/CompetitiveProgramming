use std::{collections::BTreeMap, io::{BufWriter, Stdout, Write}};

type Edge = (usize, usize, usize, usize);

fn main() {
    let scan = &mut Scanner::default();
    let (n, m) = (scan.usize(), scan.usize());
    
    let mut alive = BTreeMap::new();
    let mut edges: Vec<Edge> = vec![];
    let mut queries = vec![None; m];
    let mut dsu = DisjointSet::new(n+1);

    for i in 0..m {
        let (kind, u, v) = (scan.usize(), scan.usize(), scan.usize());
        let (u, v) = if u < v { (u, v) } else { (v, u) };
        match kind {
            1 => {
                let eid = edges.len();
                alive.entry((u, v)).or_insert((i, eid));
                edges.push((u, v, i, 0));
            }
            2 => {
                let (_, eid) = alive.get(&(u, v)).unwrap().clone();
                edges[eid].3 = i-1;
                alive.remove(&(u, v)).unwrap();
            }
            3 => {
                queries[i] = Some((u, v));
            }
            _ => panic!()
        }
    }

    for (_, (_, eid)) in &alive {
        edges[*eid].3 = m;
    }
    alive.clear();

    let mut writer = BufWriter::new(std::io::stdout());
    process_queries(0, m-1, &mut dsu, &queries, edges, &mut writer);
}

fn process_queries(
    l: usize,
    r: usize,
    dsu: &mut DisjointSet,
    queries: &[Option<(usize, usize)>],
    edges: Vec<Edge>,
    writer: &mut BufWriter<Stdout>) {
    let time = dsu.current();
    let mut unused = vec![];
    for &(u, v, el, er) in &edges {
        if el <= l && r <= er {
            dsu.union_nodes(u, v);
        } else {
            unused.push((u, v, el, er));
        }
    }

    if l == r {
        if let Some((u, v)) = queries[l] {
            let answer = if dsu.find_parent(u) == dsu.find_parent(v) { 1 } else { 0 };
            writeln!(writer, "{answer}").ok();
        }
    } else {
        let m = (l+r) / 2;
        let left_edges = unused.iter()
            .filter(|(_, _, el, er)| have_inter(l, m, *el, *er))
            .cloned()
            .collect::<Vec<_>>();
        let right_edges = unused.iter()
            .filter(|(_, _, el, er)| have_inter(m+1, r, *el, *er))
            .cloned()
            .collect::<Vec<_>>();

        process_queries(l, m, dsu, queries, left_edges, writer);
        process_queries(m+1, r, dsu, queries, right_edges, writer);    
    }
    dsu.revert(time);
}

fn have_inter(l1: usize, r1: usize, l2: usize, r2: usize) -> bool {
    !(r1 < l2 || r2 < l1)
}

enum DSUOperation {
    ChangeParent {
        index: usize,
        from: usize,
    },
    AddSize {
        index: usize,
        added: usize
    }
}

struct DisjointSet {
    parent: Vec<usize>,
    size: Vec<usize>,
    history: Vec<DSUOperation>
}

impl DisjointSet {
    fn new(size: usize) -> DisjointSet {
        let parent = (0..size).collect();
        let size = vec![1; size];
        let history = vec![];

        DisjointSet {
            parent, size, history
        }
    }

    fn current(&self) -> usize {
        self.history.len()
    }

    fn revert(&mut self, time: usize) {
        while self.history.len() > time {
            match self.history.pop().unwrap() {
                DSUOperation::ChangeParent { index, from, .. } => {
                    self.parent[index] = from;
                },
                DSUOperation::AddSize { index, added } => {
                    self.size[index] -= added;
                },
            }
        }
    } 

    fn find_parent(&self, start: usize) -> usize {
        if self.parent[start] == start {
            start
        } else {
            self.find_parent(self.parent[start])
        }
    }

    fn union_nodes(&mut self, x: usize, y: usize) {
        let x = self.find_parent(x);
        let y = self.find_parent(y);
        if x != y {
            let (small, large) = if self.size[x] < self.size[y] {
                (x, y)
            } else {
                (y, x)
            };
            self.change_parent(small, large);
            self.add_size(large, self.size[small]);
        }
    }

    fn change_parent(&mut self, index: usize, new_parent: usize) {
        self.history.push(DSUOperation::ChangeParent {
            index,
            from: self.parent[index]
        });
        self.parent[index] = new_parent;
    }

    fn add_size(&mut self, index: usize, add: usize) {
        self.history.push(DSUOperation::AddSize {
            index, added: add
        });
        self.size[index] += add;
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
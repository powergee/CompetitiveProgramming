use std::io::{stdout, BufWriter, Write};

fn main() {
    let mut input = In::stdin();
    let (n, ma, mb): (usize, usize, usize) = (input.read(), input.read(), input.read());
    let mut next = vec![None; n + 1];
    let mut mand_group = DisjointSet::new(n + 1);
    let mut taken = vec![false; n + 1];

    for i in 0..ma + mb {
        let (u, v): (usize, usize) = (input.read(), input.read());
        next[u] = Some(v);
        if ma <= i {
            mand_group.union_nodes(v, u);
        }
    }

    let mut next_group = DisjointSet::new(n + 1);
    let mut writer = BufWriter::new(stdout().lock());
    for _ in 0..input.read::<usize>() {
        let mut u = input.read();
        let answer = loop {
            u = converge(u, &mut next_group, &mut mand_group);
            if !taken[u] {
                taken[u] = true;
                break u as isize;
            } else if let Some(v) = next[u] {
                next_group.union_nodes(u, v);
                u = next_group.find_parent(u);
            } else {
                break -1;
            }
        };
        writeln!(writer, "{answer}").unwrap();
    }
}

fn converge(mut u: usize, ng: &mut DisjointSet, mg: &mut DisjointSet) -> usize {
    loop {
        let v = ng.find_parent(mg.find_parent(u));
        if u == v {
            break;
        }
        u = v;
    }
    u
}

struct DisjointSet {
    parent: Vec<usize>,
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

    fn union_nodes(&mut self, chi: usize, par: usize) {
        let x_par = self.find_parent(chi);
        let y_par = self.find_parent(par);
        self.parent[x_par] = y_par;
    }
}

struct In(std::str::SplitAsciiWhitespace<'static>, String);

impl In {
    fn stdin() -> Self {
        let buf = std::io::read_to_string(std::io::stdin().lock()).unwrap();
        let iter = unsafe { std::mem::transmute(buf.trim().split_ascii_whitespace()) };
        Self(iter, buf)
    }

    fn read<T: std::str::FromStr + std::fmt::Debug>(&mut self) -> T {
        self.0.next().and_then(|s| s.parse::<T>().ok()).unwrap()
    }
}

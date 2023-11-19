use std::{
    collections::HashMap,
    fmt::Debug,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, Write},
    str::FromStr,
};

fn main() {
    let mut stdin = stdin().lock();
    let n = read::<usize>(&mut stdin);
    let mut arr = (0..n)
        .map(|_| read::<usize>(&mut stdin))
        .collect::<Vec<_>>();

    let mut map = HashMap::new();
    let mut sorted = arr.clone();
    sorted.sort_unstable();
    for v in sorted {
        let len = map.len() + 1;
        map.entry(v).or_insert(len);
    }
    for v in &mut arr {
        *v = *map.get(v).unwrap();
    }

    let mut tree = FenwickTree::new(n + 1);
    let mut writer = BufWriter::new(stdout().lock());
    for i in 0..n {
        writeln!(writer, "{}", tree.query(n) - tree.query(arr[i]) + 1).unwrap();
        tree.update(arr[i], 1);
    }
}

fn read<T>(stdin: &mut StdinLock<'_>) -> T
where
    T: FromStr,
    T::Err: Debug,
{
    let buf = &mut String::new();
    stdin.read_line(buf).unwrap();
    buf.trim().parse::<T>().unwrap()
}

struct FenwickTree {
    tree: Vec<isize>,
}

impl FenwickTree {
    fn new(count: usize) -> Self {
        Self {
            tree: vec![0; count + 1],
        }
    }

    /// `end` is 1-indexed.
    fn query(&self, end: usize) -> isize {
        debug_assert!(end > 0);
        let mut end = end as isize;
        let mut result = 0;
        while end > 0 {
            result += self.tree[end as usize];
            end -= end & -end;
        }
        result
    }

    /// `pos` is 1-indexed.
    fn update(&mut self, pos: usize, add: isize) {
        debug_assert!(pos > 0);
        let mut pos = pos as isize;
        while (pos as usize) < self.tree.len() {
            self.tree[pos as usize] += add;
            pos += pos & -pos;
        }
    }
}

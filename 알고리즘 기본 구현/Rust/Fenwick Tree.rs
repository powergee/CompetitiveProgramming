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

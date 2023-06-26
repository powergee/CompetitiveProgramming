use std::{
    cell::RefCell,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let (r, c, w) = (io.usize(), io.usize(), io.usize());
    let map: Vec<Vec<bool>> = (0..r)
        .map(|_| {
            io.next::<String>()
                .into_bytes()
                .into_iter()
                .map(|b| b == b'1')
                .collect()
        })
        .collect();

    let dsu = RefCell::new(DisjointSet::new(r * c));
    let is_possible = |bound: usize| -> bool {
        let mut dsu = dsu.borrow_mut();
        dsu.init();
        let mut left = 0;
        let mut used = 0;
        while left < c {
            used += 1;
            if used > w + 1 {
                return false;
            }
            for i in 0..r {
                unsafe { dsu.init_unchecked(i * c + left) };
            }

            let mut j = left;
            'expand: while j < c {
                for i in 0..r {
                    if i > 0 && map[i][j] && map[i - 1][j] {
                        dsu.union_nodes(i * c + j, (i - 1) * c + j);
                    }
                    if left < j && map[i][j - 1] && map[i][j] {
                        dsu.union_nodes(i * c + j - 1, i * c + j);
                    }
                    if map[i][j] && dsu.comp_size(i * c + j) > bound {
                        break 'expand;
                    }
                }
                j += 1;
            }

            if j == left {
                return false;
            }
            left = j;
        }

        true
    };

    let mut left = 0;
    let mut right = r * c;
    while left < right {
        let mid = (left + right) / 2;
        if is_possible(mid) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    writeln!(io.writer, "{left}").unwrap();
}

struct DisjointSet {
    parent: Vec<usize>,
    size: Vec<usize>,
}

impl DisjointSet {
    fn new(size: usize) -> DisjointSet {
        let parent = (0..size).collect();
        let size = vec![1; size];
        DisjointSet { parent, size }
    }

    fn init(&mut self) {
        self.parent.iter_mut().enumerate().for_each(|(i, p)| *p = i);
        self.size.iter_mut().for_each(|s| *s = 1);
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

    fn comp_size(&mut self, x: usize) -> usize {
        let p = self.find_parent(x);
        self.size[p]
    }

    unsafe fn init_unchecked(&mut self, x: usize) {
        self.parent[x] = x;
        self.size[x] = 1;
    }

    fn union_nodes(&mut self, x: usize, y: usize) {
        let x_par = self.find_parent(x);
        let y_par = self.find_parent(y);
        if x_par != y_par {
            self.parent[x_par] = y_par;
            self.size[y_par] += self.size[x_par];
        }
    }
}

/// Modified EbTech's Scanner
pub struct IO<R, W: Write> {
    reader: R,
    writer: BufWriter<W>,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
}

impl IO<StdinLock<'static>, StdoutLock<'static>> {
    pub fn stdio() -> Self {
        Self::new(stdin().lock(), stdout().lock())
    }
}

impl<R: BufRead, W: Write> IO<R, W> {
    pub fn new(reader: R, writer: W) -> Self {
        Self {
            reader,
            writer: BufWriter::new(writer),
            buf_str: String::new(),
            buf_iter: "".split_whitespace(),
        }
    }

    #[inline]
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader
                .read_line(&mut self.buf_str)
                .expect("Failed read");
            self.buf_iter = unsafe { std::mem::transmute(self.buf_str.split_whitespace()) };
        }
    }
}

macro_rules! io_shortcut {
    ($scan_type:ident, $single_ident:ident, $multi_ident:ident) => {
        impl<R: BufRead, W: Write> IO<R, W> {
            #[inline]
            #[allow(unused)]
            fn $single_ident(&mut self) -> $scan_type {
                self.next()
            }
            #[inline]
            #[allow(unused)]
            fn $multi_ident(&mut self, n: usize) -> Vec<$scan_type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    };
}
io_shortcut!(usize, usize, usizes);

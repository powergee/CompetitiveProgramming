use std::{
    collections::VecDeque,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let (n, m) = (io.usize(), io.usize());
    let mut graph = vec![vec![]; n + 1];
    for _ in 0..m {
        let (u, v) = (io.usize(), io.usize());
        graph[u].push(v);
        graph[v].push(u);
    }
    for v in 1..n + 1 {
        graph[v].sort_unstable();
    }

    let mut dist = vec![0; n + 1];
    let mut dist_rev = vec![vec![]; n + 1];
    let mut q = VecDeque::new();
    q.push_back(1);
    dist[1] = 1;
    dist_rev[1].push(1);

    while let Some(curr) = q.pop_front() {
        for &next in &graph[curr] {
            if dist[next] != 0 {
                continue;
            }
            dist[next] = dist[curr] + 1;
            dist_rev[dist[curr] + 1].push(next);
            q.push_back(next);
        }
    }

    const MOD: usize = 1000000007;
    let mut answer = 1;
    for count in dist_rev.iter().skip(1) {
        answer *= count.len() + 1;
        answer %= MOD;
    }
    writeln!(io.writer, "{}", answer - 1).unwrap();
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

macro_rules! io_shortcut {(
    $(($type:ident, $types:ident))*
) => (
    $(
        impl<R: BufRead, W: Write> IO<R, W> {
            #[inline]
            #[allow(unused)]
            fn $type(&mut self) -> $type {
                self.next()
            }
            #[inline]
            #[allow(unused)]
            fn $types(&mut self, n: usize) -> Vec<$type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    )*
)}

io_shortcut! {
    (u8, u8s) (u16, u16s) (u32, u32s) (u64, u64s) (u128, u128s)
    (i8, i8s) (i16, i16s) (i32, i32s) (i64, i64s) (i128, i128s)
    (usize, usizes) (isize, isizes) (f64, f64s)
}

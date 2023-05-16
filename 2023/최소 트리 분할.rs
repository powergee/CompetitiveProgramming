use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();

    let n = io.usize();
    let mut weights = vec![usize::MAX];
    weights.extend(io.usizes(n));

    let mut graph = vec![vec![]; n + 1];
    for _ in 0..n - 1 {
        let (u, v) = (io.usize(), io.usize());
        graph[u].push(v);
        graph[v].push(u);
    }

    let (start_w, start_v) = weights
        .iter()
        .enumerate()
        .map(|(i, w)| (*w, i))
        .min()
        .unwrap();
    let mut answer = start_w;
    let mut visited = vec![false; n + 1];
    visited[start_v] = true;
    let mut st = vec![start_v];

    while let Some(curr_v) = st.pop() {
        let curr_w = weights[curr_v];
        for &next_v in &graph[curr_v] {
            let next_w = weights[next_v];
            if !visited[next_v] {
                visited[next_v] = true;
                st.push(next_v);
                if curr_w < next_w {
                    answer += next_w - curr_w;
                }
            }
        }
    }

    writeln!(io.writer, "{answer}").unwrap();
}

// Modified EbTech's Scanner
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

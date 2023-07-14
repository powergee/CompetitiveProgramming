use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let map = (0..n).map(|_| io.usizes(n)).collect::<Vec<_>>();
    let mut state = State {
        n: n as isize,
        map,
        dp: vec![vec![0; n]; n],
    };
    let mut answer = 0;
    for r in 0..n {
        for c in 0..n {
            answer = answer.max(state.max_moves(r, c));
        }
    }
    writeln!(io.writer, "{answer}",).unwrap();
}

struct State {
    n: isize,
    map: Vec<Vec<usize>>,
    dp: Vec<Vec<usize>>,
}

impl State {
    fn max_moves(&mut self, r: usize, c: usize) -> usize {
        let mut max = self.dp[r][c];
        if max != 0 {
            return max;
        }
        max = 1;
        for (dr, dc) in [(1, 0), (-1, 0), (0, 1), (0, -1)] {
            let nr = r as isize + dr;
            let nc = c as isize + dc;
            if 0 <= nr
                && nr < self.n
                && 0 <= nc
                && nc < self.n
                && self.map[r][c] < self.map[nr as usize][nc as usize]
            {
                max = max.max(1 + self.max_moves(nr as usize, nc as usize));
            }
        }
        self.dp[r][c] = max;
        max
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

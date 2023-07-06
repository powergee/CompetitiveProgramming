use std::{
    collections::VecDeque,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

const MOVE: [(isize, isize, bool); 12] = [
    (0, 1, false),
    (0, -1, false),
    (1, 0, false),
    (-1, 0, false),
    (-2, -1, true),
    (-2, 1, true),
    (-1, -2, true),
    (-1, 2, true),
    (1, -2, true),
    (1, 2, true),
    (2, -1, true),
    (2, 1, true),
];

fn main() {
    let mut io = IO::stdio();
    let (k, w, h) = (io.usize(), io.isize(), io.isize());
    let map = (0..h)
        .map(|_| (0..w).map(|_| io.usize() == 1).collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut visited = vec![vec![vec![false; k + 1]; w as usize]; h as usize];
    let mut cands = vec![usize::MAX; k + 1];
    let mut q = VecDeque::new();
    q.push_back((0, 0, 0, k));

    while let Some((curr_dist, r, c, chances)) = q.pop_front() {
        if r == h - 1 && c == w - 1 {
            cands[chances] = cands[chances].min(curr_dist);
            continue;
        }
        for (dr, dc, horse) in &MOVE {
            let nr = dr + r;
            let nc = dc + c;
            let nchances = if *horse {
                match chances.checked_sub(1) {
                    Some(val) => val,
                    None => continue,
                }
            } else {
                chances
            };
            if 0 <= nr
                && nr < h
                && 0 <= nc
                && nc < w
                && !map[nr as usize][nc as usize]
                && !visited[nr as usize][nc as usize][nchances]
            {
                visited[nr as usize][nc as usize][nchances] = true;
                q.push_back((curr_dist + 1, nr, nc, nchances))
            }
        }
    }

    let answer = cands.into_iter().min().unwrap();
    writeln!(
        io.writer,
        "{}",
        if answer == usize::MAX {
            "-1".to_string()
        } else {
            answer.to_string()
        }
    )
    .unwrap();
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
    (usize, usizes) (isize, isizes)
}

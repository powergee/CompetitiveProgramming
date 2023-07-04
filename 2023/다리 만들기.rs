use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let map = (0..n)
        .map(|_| io.usizes(n).into_iter().map(|v| v == 1).collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut visited = vec![vec![0; n]; n];
    let mut comp_id = 1;
    for i in 0..n {
        for j in 0..n {
            if map[i][j] && visited[i][j] == 0 {
                let mut stack = vec![(i, j)];
                visited[i][j] = comp_id;
                while let Some((r, c)) = stack.pop() {
                    for (dr, dc) in [(1, 0), (-1, 0), (0, 1), (0, -1)] {
                        let nr = r as isize + dr;
                        let nc = c as isize + dc;
                        if 0 <= nr
                            && nr < n as isize
                            && 0 <= nc
                            && nc < n as isize
                            && map[nr as usize][nc as usize]
                            && visited[nr as usize][nc as usize] == 0
                        {
                            visited[nr as usize][nc as usize] = comp_id;
                            stack.push((nr as usize, nc as usize));
                        }
                    }
                }
                comp_id += 1;
            }
        }
    }

    let mut answer = usize::MAX;
    for i in 0..n {
        for j in 0..n {
            for k in 0..n {
                for l in 0..n {
                    if visited[i][j] != 0 && visited[k][l] != 0 && visited[i][j] != visited[k][l] {
                        answer = answer.min(i.abs_diff(k) + j.abs_diff(l) - 1);
                    }
                }
            }
        }
    }

    writeln!(io.writer, "{answer}").unwrap();
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
    (usize, usizes)
}

use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

static mut MAP: [[i64; 3000]; 3000] = [[0; 3000]; 3000];

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();

    let map = unsafe { &mut MAP };
    for r in 0..n {
        for c in 0..n {
            map[r][c] = io.next();
        }
    }

    let mut left = n / 2 - 1;
    let mut right = n / 2;
    let mut top = n / 2 - 1;
    let mut bottom = n / 2;
    let mut total = 0;
    let mut path = String::with_capacity(2 * n);

    let mut top_sum = if 0 < top {
        let mut sum = 0;
        for c in left..right + 1 {
            sum += map[top - 1][c];
        }
        sum
    } else {
        i64::MIN
    };
    let mut bottom_sum = if bottom + 1 < n {
        let mut sum = 0;
        for c in left..right + 1 {
            sum += map[bottom + 1][c];
        }
        sum
    } else {
        i64::MIN
    };
    let mut left_sum = if 0 < left {
        let mut sum = 0;
        for r in top..bottom + 1 {
            sum += map[r][left - 1];
        }
        sum
    } else {
        i64::MIN
    };
    let mut right_sum = if right + 1 < n {
        let mut sum = 0;
        for r in top..bottom + 1 {
            sum += map[r][right + 1];
        }
        sum
    } else {
        i64::MIN
    };

    loop {
        let cands = [(top_sum, 3), (bottom_sum, 2), (left_sum, 1), (right_sum, 0)];

        let min = cands.iter().max().unwrap();
        if min.0 > 0 {
            total += min.0;
        } else {
            break;
        }
        match min.1 {
            3 => {
                top -= 1;
                path.push_str("U");
                top_sum = if 0 < top {
                    let mut sum = 0;
                    for c in left..right + 1 {
                        sum += map[top - 1][c];
                    }
                    sum
                } else {
                    i64::MIN
                };
                if 0 < left {
                    left_sum = left_sum.saturating_add(map[top][left - 1]);
                }
                if right + 1 < n {
                    right_sum = right_sum.saturating_add(map[top][right + 1]);
                }
            }
            2 => {
                bottom += 1;
                path.push_str("D");
                bottom_sum = if bottom + 1 < n {
                    let mut sum = 0;
                    for c in left..right + 1 {
                        sum += map[bottom + 1][c];
                    }
                    sum
                } else {
                    i64::MIN
                };
                if 0 < left {
                    left_sum = left_sum.saturating_add(map[bottom][left - 1]);
                }
                if right + 1 < n {
                    right_sum = right_sum.saturating_add(map[bottom][right + 1]);
                }
            }
            1 => {
                left -= 1;
                path.push_str("L");
                left_sum = if 0 < left {
                    let mut sum = 0;
                    for r in top..bottom + 1 {
                        sum += map[r][left - 1];
                    }
                    sum
                } else {
                    i64::MIN
                };
                if 0 < top {
                    top_sum = top_sum.saturating_add(map[top - 1][left]);
                }
                if bottom + 1 < n {
                    bottom_sum = bottom_sum.saturating_add(map[bottom + 1][left]);
                }
            }
            0 => {
                right += 1;
                path.push_str("R");
                right_sum = if right + 1 < n {
                    let mut sum = 0;
                    for r in top..bottom + 1 {
                        sum += map[r][right + 1];
                    }
                    sum
                } else {
                    i64::MIN
                };
                if 0 < top {
                    top_sum = top_sum.saturating_add(map[top - 1][right]);
                }
                if bottom + 1 < n {
                    bottom_sum = bottom_sum.saturating_add(map[bottom + 1][right]);
                }
            }
            _ => unreachable!(),
        }
    }

    writeln!(io.writer, "{total}\n{path}").unwrap();
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

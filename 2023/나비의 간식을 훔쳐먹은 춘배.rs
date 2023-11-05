use std::{
    cell::RefCell,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let n = io.u32();
    let (h, d, k) = (io.u32(), io.u32(), io.u32());
    let dams = io.u32s(n as _);
    let state = State::new(n, h, d, k, dams);
    writeln!(
        io.writer,
        "{}",
        state.max_health(h as _, d, Chance::NotUsed, 0)
    )
    .unwrap();
}

#[derive(Clone, Copy, PartialEq, Eq)]
enum Chance {
    NotUsed = 0,
    Affecting = 1,
    Used = 2,
}

impl Chance {
    fn affecting(self) -> bool {
        self == Chance::Affecting
    }

    fn expire_if_affecting(self) -> Self {
        if self.affecting() {
            Self::Used
        } else {
            self
        }
    }
}

struct State {
    n: u32,
    k: u32,
    dams: Vec<u32>,
    /// dp[curr hp <= h][dist <= d + n*k][chance enum < 4][index < n]
    dp: RefCell<Vec<Vec<Vec<Vec<Option<i32>>>>>>,
}

impl State {
    fn new(n: u32, h: u32, d: u32, k: u32, dams: Vec<u32>) -> Self {
        Self {
            n,
            k,
            dams,
            dp: RefCell::new(vec![
                vec![
                    vec![vec![None; n as usize]; 3];
                    (d + n * k + 1) as usize
                ];
                h as usize + 1
            ]),
        }
    }

    fn max_health(&self, curr_hp: i32, dist: u32, chance: Chance, time: usize) -> i32 {
        if curr_hp <= 0 {
            return -1;
        }
        if self.n <= time as _ {
            return curr_hp as _;
        }
        if let Some(memo) = self.dp.borrow()[curr_hp as usize][dist as usize][chance as usize][time]
        {
            return memo;
        }

        let result = [
            self.max_health(
                curr_hp
                    - if chance.affecting() {
                        0
                    } else {
                        self.dams[time].checked_sub(dist).unwrap_or(0) / 2
                    } as i32,
                dist,
                chance.expire_if_affecting(),
                time + 1,
            ),
            self.max_health(
                curr_hp
                    - if chance.affecting() {
                        0
                    } else {
                        self.dams[time].checked_sub(dist + self.k).unwrap_or(0)
                    } as i32,
                dist + self.k,
                chance.expire_if_affecting(),
                time + 1,
            ),
            if chance == Chance::NotUsed {
                self.max_health(
                    curr_hp
                        - if chance.affecting() {
                            0
                        } else {
                            self.dams[time].checked_sub(dist).unwrap_or(0)
                        } as i32,
                    dist,
                    Chance::Affecting,
                    time + 1,
                )
            } else {
                -1
            },
        ]
        .iter()
        .max()
        .copied()
        .unwrap();

        self.dp.borrow_mut()[curr_hp as usize][dist as usize][chance as usize][time] = Some(result);
        result
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
            #[allow(unused)]
            fn $type(&mut self) -> $type {
                self.next()
            }
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

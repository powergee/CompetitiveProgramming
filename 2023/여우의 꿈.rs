use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

const MOD: usize = 1000000007;

fn main() {
    let mut io = IO::stdio();
    let (n, mut curr_pos) = (io.usize(), io.usize());
    let target_pos = io.usizes(n);
    let mut answer = 0;
    for (i, p) in target_pos.into_iter().rev().enumerate() {
        if p == curr_pos {
            continue;
        }
        answer += mod_pow(2, n - i - 1);
        answer %= MOD;
        curr_pos = if curr_pos != 1 && p != 1 {
            1
        } else if curr_pos != 2 && p != 2 {
            2
        } else {
            3
        };
    }
    writeln!(io.writer, "{answer}").unwrap();
}

fn mod_pow(val: usize, mut exp: usize) -> usize {
    let mut result = 1;
    let mut sub_power = val % MOD;

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * sub_power) % MOD;
        }
        exp /= 2;
        sub_power = (sub_power * sub_power) % MOD;
    }
    result
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

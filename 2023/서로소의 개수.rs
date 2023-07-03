use std::{
    cell::RefCell,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

const P: usize = 10000003;

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let arr = io.usizes(n);
    let state = State::new(n, arr);

    let mut answer = 0;
    for i in 0..n {
        answer += state.count(i, state.arr[i]);
        answer %= P as u32;
    }
    writeln!(io.writer, "{answer}").unwrap();
}

struct State {
    n: usize,
    arr: Vec<usize>,
    dp: RefCell<Vec<Vec<Option<u32>>>>,
}

impl State {
    fn new(n: usize, arr: Vec<usize>) -> Self {
        let max = *arr.iter().max().unwrap();
        Self {
            n,
            arr,
            dp: RefCell::new(vec![vec![None; max + 1]; n]),
        }
    }

    fn count(&self, start: usize, curr_gcd: usize) -> u32 {
        if start > self.n {
            return 0;
        }
        if let Some(dp) = self.dp.borrow_mut()[start][curr_gcd] {
            return dp;
        }

        if curr_gcd == 1 {
            let result = mod_pow(2, self.n - start - 1) as _;
            self.dp.borrow_mut()[start][curr_gcd] = Some(result);
            return result;
        }

        let mut result = 0;
        for i in start + 1..self.n {
            result += self.count(i, gcd(curr_gcd, self.arr[i]));
            result %= P as u32;
        }
        self.dp.borrow_mut()[start][curr_gcd] = Some(result);
        return result;
    }
}

fn gcd(a: usize, b: usize) -> usize {
    if b == 0 {
        a
    } else {
        gcd(b, a % b)
    }
}

fn mod_pow(val: usize, mut exp: usize) -> usize {
    let mut result = 1;
    let mut sub_power = val % P;

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * sub_power) % P;
        }
        exp /= 2;
        sub_power = (sub_power * sub_power) % P;
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
    (usize, usizes)
}

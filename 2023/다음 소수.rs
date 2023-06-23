use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    for _ in 0..n {
        let mut start = io.next();
        while !is_prime(start) {
            start += 1;
        }
        writeln!(io.writer, "{start}").unwrap();
    }
}

const ROBUST_TEST_SETS: &'static [(u64, &'static [u64])] = &[
    (2047, &[2]),
    (1373653, &[2, 3]),
    (9080191, &[31, 73]),
    (25326001, &[2, 3, 5]),
    (3215031751, &[2, 3, 5, 7]),
    (4759123141, &[2, 7, 61]),
    (1122004669633, &[2, 13, 23, 1662803]),
    (2152302898747, &[2, 3, 5, 7, 11]),
    (3474749660383, &[2, 3, 5, 7, 11, 13]),
    (341550071728321, &[2, 3, 5, 7, 11, 13, 17]),
    (3825123056546413051, &[2, 3, 5, 7, 11, 13, 17, 19, 23]),
    (0, &[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]),
];

fn mod_pow(val: u64, mut exp: u64, div: u64) -> u128 {
    let mut result: u128 = 1;
    let mut sub_power = (val % div) as u128;

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * sub_power) % (div as u128);
        }
        exp /= 2;
        sub_power = (sub_power * sub_power) % (div as u128);
    }
    result
}

fn test_miller_rabin(n: u64, a: u64) -> bool {
    let mut d = n - 1;
    while d % 2 == 0 {
        d /= 2;
    }

    let mut x = mod_pow(a, d, n);
    if x == 1 || x == (n - 1) as u128 {
        return true;
    }
    while d != n - 1 {
        x = (x * x) % n as u128;
        d *= 2;
        if x == (n - 1) as u128 {
            return true;
        }
    }
    false
}

fn is_prime(n: u64) -> bool {
    if n == 2 {
        return true;
    } else if n <= 1 || n % 2 == 0 {
        return false;
    }

    let index = ROBUST_TEST_SETS
        .iter()
        .position(|pair| n < pair.0)
        .unwrap_or(ROBUST_TEST_SETS.len() - 1);

    let tests = &ROBUST_TEST_SETS[index].1;
    tests.iter().all(|a| test_miller_rabin(n, *a))
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
io_shortcut!(String, string, strings);

use std::{
    cell::RefCell,
    collections::HashMap,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let primes = primes(n);
    let state = State {
        primes,
        dp: RefCell::new(HashMap::new()),
    };

    writeln!(
        io.writer,
        "{}",
        if let Some(answer) = state.find(n, 4) {
            answer
                .into_iter()
                .map(|v| v.to_string())
                .collect::<Vec<_>>()
                .join(" ")
        } else {
            "-1".to_string()
        }
    )
    .unwrap();
}

struct State {
    primes: Vec<usize>,
    dp: RefCell<HashMap<(usize, usize), Vec<usize>>>,
}

impl State {
    fn find(&self, target: usize, remain: usize) -> Option<Vec<usize>> {
        if remain == 0 {
            return if target == 0 { Some(vec![]) } else { None };
        }
        if target <= 1 {
            return None;
        }
        if let Some(dp) = self.dp.borrow().get(&(target, remain)) {
            return Some(dp.clone());
        }
        let mut bound = self.primes.partition_point(|&x| x < target);
        if bound < self.primes.len() && target < self.primes[bound] {
            bound -= 1;
        }
        for p in self.primes.iter().take(bound + 1).rev() {
            if let Some(mut prev) = self.find(target - *p, remain - 1) {
                prev.push(*p);
                self.dp.borrow_mut().insert((target, remain), prev.clone());
                return Some(prev);
            }
        }
        None
    }
}

fn primes(last: usize) -> Vec<usize> {
    if last < 2 {
        return vec![];
    }

    let mut is_prime = vec![true; last + 1];
    is_prime[0] = false;
    is_prime[1] = false;
    let mut div = 2;

    while div * div <= last {
        if is_prime[div] {
            for i in (div * div..=last).step_by(div) {
                is_prime[i] = false;
            }
        }
        div += 1;
    }

    is_prime
        .into_iter()
        .enumerate()
        .skip(2)
        .filter_map(|(x, p)| if p { Some(x) } else { None })
        .collect()
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

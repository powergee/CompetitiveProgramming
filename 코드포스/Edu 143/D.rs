#![allow(unused)]
use std::{
    collections::VecDeque,
    io::{BufRead, BufWriter, Write},
};

pub struct CombCalc {
    fact_dp: Vec<usize>,
    bound: usize,
}

impl CombCalc {
    pub fn new(size: usize, bound: usize) -> Self {
        let mut fact_dp = Vec::with_capacity(size + 1);
        fact_dp.push(1);
        for i in 1..=size {
            fact_dp.push((*fact_dp.last().unwrap() * i) % bound);
        }
        Self { fact_dp, bound }
    }

    pub fn comb(&self, n: usize, k: usize) -> usize {
        if n < k {
            return 0;
        }
        (self.fact_dp[n] * self.mod_inverse((self.fact_dp[n - k] * self.fact_dp[k]) % self.bound))
            % self.bound
    }

    pub fn homo_comb(&self, n: usize, k: usize) -> usize {
        self.comb(n + k - 1, n - 1)
    }

    pub fn catalan(&self, n: usize) -> usize {
        (self.comb(2 * n, n) * self.mod_inverse(n + 1)) % self.bound
    }

    fn mod_pow(&self, val: usize, exp: usize) -> usize {
        if val == 0 {
            return 0;
        } else if exp == 0 {
            return 1;
        }
        let pow = self.mod_pow(val, exp / 2);
        (((pow * pow) % self.bound) * (if exp % 2 == 0 { 1 } else { val })) % self.bound
    }

    fn mod_inverse(&self, val: usize) -> usize {
        self.mod_pow(val, self.bound - 2)
    }
}

const MOD: usize = 998244353;

fn main() {
    let stdin = std::io::stdin();
    let stdout = std::io::stdout();
    let io = &mut IO::new(stdin.lock(), stdout.lock());

    let n = io.usize();
    let w = io.usizes(n);
    let mut profit = Vec::with_capacity(n / 3);
    for i in 0..n / 3 {
        let (a, b, c) = (w[i * 3], w[i * 3 + 1], w[i * 3 + 2]);
        profit.push([a + b, b + c, c + a]);
    }
    for seg in &mut profit {
        seg.sort_by(|a, b| b.cmp(a));
    }

    let mut cases = 1;
    for [a, b, c] in &profit {
        if a == c {
            cases *= 3;
        } else if a == b {
            cases *= 2;
        }
        cases %= MOD;
    }
    dbg!(cases);

    let calc = CombCalc::new(n / 3, MOD);
    writeln!(io.writer, "{}", (calc.comb(n / 3, n / 6) * cases) % MOD);
}

// Modified EbTech's Scanner
pub struct IO<R, W: Write> {
    reader: R,
    writer: BufWriter<W>,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
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
io_shortcut!(i64, i64, i64s);
io_shortcut!(u64, u64, u64s);
io_shortcut!(usize, usize, usizes);
io_shortcut!(f64, f64, f64s);
io_shortcut!(String, string, strings);

use std::marker::PhantomData;

// From https://github.com/EgorKulikov/rust_algo/blob/master/algo_lib/src/misc/recursive_function.rs
macro_rules! recursive_function {
    ($name: ident, $trait: ident, ($($type: ident $arg: ident,)*)) => {
        pub trait $trait<$($type, )*Output> {
            fn call(&mut self, $($arg: $type,)*) -> Output;
        }

        pub struct $name<F, $($type, )*Output>
        where
            F: FnMut(&mut dyn $trait<$($type, )*Output>, $($type, )*) -> Output,
        {
            f: std::cell::UnsafeCell<F>,
            $($arg: PhantomData<$type>,
            )*
            phantom_output: PhantomData<Output>,
        }

        impl<F, $($type, )*Output> $name<F, $($type, )*Output>
        where
            F: FnMut(&mut dyn $trait<$($type, )*Output>, $($type, )*) -> Output,
        {
            pub fn new(f: F) -> Self {
                Self {
                    f: std::cell::UnsafeCell::new(f),
                    $($arg: Default::default(),
                    )*
                    phantom_output: Default::default(),
                }
            }
        }

        impl<F, $($type, )*Output> $trait<$($type, )*Output> for $name<F, $($type, )*Output>
        where
            F: FnMut(&mut dyn $trait<$($type, )*Output>, $($type, )*) -> Output,
        {
            fn call(&mut self, $($arg: $type,)*) -> Output {
                unsafe { (*self.f.get())(self, $($arg, )*) }
            }
        }
    }
}

recursive_function!(RecursiveFunction0, Callable0, ());
recursive_function!(RecursiveFunction, Callable, (Arg arg,));
recursive_function!(RecursiveFunction2, Callable2, (Arg1 arg1, Arg2 arg2,));
recursive_function!(RecursiveFunction3, Callable3, (Arg1 arg1, Arg2 arg2, Arg3 arg3,));
recursive_function!(RecursiveFunction4, Callable4, (Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4,));
recursive_function!(RecursiveFunction5, Callable5, (Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5,));
recursive_function!(RecursiveFunction6, Callable6, (Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6,));
recursive_function!(RecursiveFunction7, Callable7, (Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7,));
recursive_function!(RecursiveFunction8, Callable8, (Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8,));
recursive_function!(RecursiveFunction9, Callable9, (Arg1 arg1, Arg2 arg2, Arg3 arg3, Arg4 arg4, Arg5 arg5, Arg6 arg6, Arg7 arg7, Arg8 arg8, Arg9 arg9,));

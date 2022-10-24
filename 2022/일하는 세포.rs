use std::io::{BufWriter, self, Write};

fn main() {
    let scan = &mut Scanner::default();
    let (t, n, d) = (scan.usize(), scan.usize(), scan.usize());
    
    let trans = (0..t)
        .map(|_| {
            let m = scan.usize();
            let mut trans = Matrix::new(n, n, 0);
            for _ in 0..m {
                let (a, b, c) = (scan.usize(), scan.usize(), scan.u64());
                *trans.get_mut(a-1, b-1) += c;
            }
            trans
        })
        .collect::<Vec<_>>();

    let trans_acc = trans
        .iter()
        .scan(Matrix::identity(n), |prev, x| {
            *prev = prev.mul(x);
            Some(prev.clone())
        })
        .collect::<Vec<_>>();
    
    let mut answer = trans_acc.last().unwrap().pow(d/t);
    if d % t > 0 {
        answer = answer.mul(&trans_acc[d%t-1]);
    }
    
    let stdout = io::stdout();
    let mut writer = BufWriter::new(stdout.lock());
    for i in 0..answer.rows() {
        for j in 0..answer.cols() {
            write!(writer, "{} ", answer.get(i, j)).ok();
        }
        writeln!(writer).ok();
    }
}

const MOD: u64 = 1000000007;

#[derive(Clone)]
struct Matrix {
    nums: Vec<Vec<u64>>
}

impl Matrix {
    pub fn new(rows: usize, cols: usize, init: u64) -> Self {
        Matrix {
            nums: vec![vec![init; cols]; rows]
        }
    }

    pub fn identity(size: usize) -> Self {
        let mut result = Matrix::new(size, size, 0);
        for i in 0..size {
            result.nums[i][i] = 1;
        }
        result
    }

    pub fn rows(&self) -> usize {
        self.nums.len()
    }

    pub fn cols(&self) -> usize {
        self.nums[0].len()
    }

    pub fn get(&self, row: usize, col: usize) -> u64 {
        self.nums[row][col]
    }

    pub fn get_mut(&mut self, row: usize, col: usize) -> &mut u64 {
        &mut self.nums[row][col]
    }

    pub fn mul(&self, rhs: &Self) -> Self {
        assert_eq!(self.cols(), rhs.rows());
        let mut result = Self::new(self.rows(), rhs.cols(), 0);
        for i in 0..self.rows() {
            for j in 0..rhs.cols() {
                for k in 0..self.cols() {
                    result.nums[i][j] += self.get(i, k) * rhs.get(k, j);
                    result.nums[i][j] %= MOD;
                }
            }
        }
        result
    }

    fn pow_rec(&self, e: usize) -> Self {
        if e == 0 {
            Self::identity(self.rows())
        } else if e == 1 {
            self.clone()
        } else {
            let sub = self.pow_rec(e/2);
            if e % 2 == 0 {
                sub.mul(&sub)
            } else {
                sub.mul(&sub).mul(self)
            }
        }
    }

    pub fn pow(&self, e: usize) -> Self {
        assert_eq!(self.rows(), self.cols());
        self.pow_rec(e)
    }
}

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            std::io::stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

macro_rules! scanner_shortcut {
    ($scan_type:ident, $single_scan_ident:ident, $multi_scan_ident:ident) => {
        impl Scanner {
            #[allow(unused)]
            fn $single_scan_ident(&mut self) -> $scan_type {
                self.next()
            }
            #[allow(unused)]
            fn $multi_scan_ident(&mut self, n: usize) -> Vec<$scan_type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    };
}
scanner_shortcut!(i32, i32, i32s);
scanner_shortcut!(i64, i64, i64s);
scanner_shortcut!(isize, isize, isizes);
scanner_shortcut!(u32, u32, u32s);
scanner_shortcut!(u64, u64, u64s);
scanner_shortcut!(usize, usize, usizes);
scanner_shortcut!(f64, f64, f64s);
scanner_shortcut!(String, string, strings);
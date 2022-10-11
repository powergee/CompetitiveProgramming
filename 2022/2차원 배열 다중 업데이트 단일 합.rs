use std::io::BufRead;

fn main() {
    let stdin = std::io::stdin();
    let scan = &mut Scanner::new(stdin.lock());

    let (n, m) = (scan.usize(), scan.usize());
    let init = (0..n).map(|_| scan.i64s(n)).collect::<Vec<_>>();
    let mut add = vec![vec![0; n+1]; n+1];

    for _ in 0..m-1 {
        let (op, i1, j1, i2, j2, val) = 
            (scan.usize(), scan.usize(), scan.usize(), scan.usize(), scan.usize(), scan.i64());
        assert!(op == 1);
        add[i1][j1] += val;
        add[i1][j2+1] += -val;
        add[i2+1][j1] += -val;
        add[i2+1][j2+1] += val;
    }
    
    for i in 0..=n {
        for j in 1..=n {
            add[i][j] += add[i][j-1];
        }
    }
    for j in 0..=n {
        for i in 1..=n {
            add[i][j] += add[i-1][j];
        }
    }

    let (op, i1, j1, i2, j2) = 
        (scan.usize(), scan.usize(), scan.usize(), scan.usize(), scan.usize());
    assert!(op == 2);

    let mut answer = 0;
    for i in i1..=i2 {
        for j in j1..=j2 {
            answer += init[i][j] + add[i][j];
        }
    }

    println!("{answer}");
}

// From EbTech
pub struct Scanner<B> {
    reader: B,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
}

impl<B: BufRead> Scanner<B> {
    pub fn new(reader: B) -> Self {
        Self {
            reader,
            buf_str: String::new(),
            buf_iter: "".split_whitespace()
        }
    }

    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader.read_line(&mut self.buf_str).expect("Failed read");
            self.buf_iter = unsafe { std::mem::transmute(self.buf_str.split_whitespace()) };
        }
    }
}


macro_rules! scanner_shortcut {
    ($scan_type:ident, $single_scan_ident:ident, $multi_scan_ident:ident) => {
        impl<B: BufRead> Scanner<B> {
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
fn main() {
    let scan = &mut Scanner::default();
    let n = scan.usize();
    let a = scan.i32s(n);
    let b = scan.i32s(n);

    let base = a.iter()
        .zip(b.iter())
        .fold(0, |state, curr| state + curr.0*curr.1);
    
    let diff: Vec<_> = a.iter()
        .zip(b.iter())
        .map(|(v, on)| if *on == 1 { -*v } else { *v })
        .collect();

    let mut dp = vec![0; diff.len()];
    dp[0] = diff[0];
    for i in 1..n {
        dp[i] = diff[i] + 0.max(dp[i-1]);
    }

    println!("{}", dp.iter().max().unwrap() + base);
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
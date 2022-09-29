fn main() {
    let scan = &mut Scanner::default();
    let n = scan.usize();
    let arr = scan.i32s(n);
    
    let (odd_idxs, even_idxs) = if arr.len() % 2 == 0 {
        (arr.len()/2, arr.len()/2)
    } else {
        (arr.len()/2+1, arr.len()/2)
    };

    let (odd, even): (Vec<_>, Vec<_>) = arr.into_iter()
        .partition(|n| n % 2 == 1);

    let possible = if odd.len() == odd_idxs && even.len() == even_idxs { 1 } else { 0 };
    println!("{possible}");
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
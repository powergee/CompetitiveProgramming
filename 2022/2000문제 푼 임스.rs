use std::io::BufRead;

fn main() {
    let stdin = std::io::stdin();
    let scan = &mut Scanner::new(stdin.lock());
    let coin = scan.string();
    let tokens = coin.split(".").take(2).collect::<Vec<_>>();
    let coin = tokens[0].parse::<usize>().unwrap()*100 + tokens[1].parse::<usize>().unwrap();
    let chance = (coin / 99).min(2);

    let n = scan.usize();
    let solved = scan.usizes(n);
    let max_solved = solved.iter().max().unwrap();
    let mut dp = vec![vec![0; chance+1]; n];
    
    for ch_used in 0..=chance {
        dp[n-1][ch_used] = if solved[n-1] > 0 || ch_used < chance {
            1
        } else {
            0
        }
    }
    for day in (0..n-1).rev() {
        for ch_used in 0..=chance {
            dp[day][ch_used] = if solved[day] > 0 {
                1+dp[day+1][ch_used]
            } else if ch_used < chance {
                1+dp[day+1][ch_used+1]
            } else {
                0
            }
        }
    }

    let mut answer = 0;
    for day in 0..n {
        answer = answer.max(dp[day][0]);
    }
    println!("{}\n{}", answer, *max_solved);
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
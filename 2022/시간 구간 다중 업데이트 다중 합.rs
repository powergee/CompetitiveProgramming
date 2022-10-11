use std::io::{BufRead, BufWriter, Write};

fn main() {
    let stdin = std::io::stdin();
    let scan = &mut Scanner::new(stdin.lock());

    let n = scan.usize();
    let mut updated = false;
    let mut sum = [0i64; 60*60*24+1];
    let stdout = std::io::stdout();
    let writer = &mut BufWriter::new(stdout.lock());

    for _ in 0..n {
        let op = scan.usize();
        let (s, e) = (
            parse_time(scan.string()),
            parse_time(scan.string())
        );
        if op == 1 {
            assert!(!updated);
            sum[s] += 1;
            sum[e] -= 1;
        } else {
            if !updated {
                for i in 1..sum.len() {
                    sum[i] += sum[i-1];
                }
                for i in 1..sum.len() {
                    sum[i] += sum[i-1];
                }
                updated = true;
            }
            let result = if s == 0 {
                sum[e-1]
            } else {
                sum[e-1] - sum[s-1]
            };
            writeln!(writer, "{}", result).ok();
        }
    }
}

fn parse_time(exp: String) -> usize {
    let tokens = exp.split(":")
        .map(|v| v.parse::<usize>().unwrap())
        .collect::<Vec<_>>();
    
    60*60*tokens[0] + 60*tokens[1] + tokens[2]
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
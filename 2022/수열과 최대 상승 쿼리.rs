use std::io::BufWriter;
use std::io::Write;

fn main() {
    let scan = &mut Scanner::default();
    let n = scan.usize();
    let mut arr = scan.i32s(n, 0);
    let sqrt = (n as f64).sqrt() as usize;

    let mut blocks = (0..(arr.len()-1)/sqrt+1)
        .map(|i| calc_block(i*sqrt, (i+1)*sqrt, &arr))
        .collect::<Vec<_>>();

    let q = scan.usize();
    let mut writer = BufWriter::new(std::io::stdout());
    for _ in 0..q {
        let t = scan.usize();
        if t == 1 {
            let (t, x) = (scan.usize()-1, scan.i32());
            arr[t] = x;
            let bid = t/sqrt;
            blocks[bid] = calc_block(bid*sqrt, (bid+1)*sqrt, &arr);
        } else {
            let (l, r) = (scan.usize()-1, scan.usize()-1);
            let bl = l/sqrt;
            let br = r/sqrt;
            let answer = if bl == br {
                calc_block(l, r+1, &arr).2
            } else {
                let local = [calc_block(l, (bl+1)*sqrt, &arr)]
                    .iter()
                    .copied()
                    .chain(blocks.iter().skip(bl+1).take(br-bl-1).copied())
                    .chain([calc_block(br*sqrt, r+1, &arr)].iter().copied())
                    .collect::<Vec<_>>();
                
                let mut result = local.iter().max_by_key(|v| v.2).unwrap().2;
                let mut local_min = local[0].0;
                for i in 1..local.len() {
                    result = result.max(local[i].1 - local_min);
                    local_min = local_min.min(local[i].0);
                }
                result
            };
            writeln!(writer, "{answer}").unwrap();
        }
    }
}

fn calc_block(start: usize, end: usize, arr: &Vec<i32>) -> (i32, i32, i32) {
    let mut local_min = arr[start];
    let mut local_max = arr[start];
    let mut result = 0;
    for i in (start+1)..(end.min(arr.len())) {
        result = result.max(arr[i]-local_min);
        local_min = local_min.min(arr[i]);
        local_max = local_max.max(arr[i]);
    }
    (local_min, local_max, result)
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
            fn $multi_scan_ident(&mut self, n: usize, padding: usize) -> Vec<$scan_type> {
                std::iter::repeat(Default::default())
                    .take(padding)
                    .chain((0..n).map(|_| self.next()))
                    .collect()
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
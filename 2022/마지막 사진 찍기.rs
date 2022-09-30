use std::{collections::VecDeque, io::BufWriter, io::Write};

fn main() {
    let scan = &mut Scanner::default();
    let t = scan.usize();
    let writer = &mut BufWriter::new(std::io::stdout());
    for _ in 0..t {
        let k = scan.usize();
        let cap = scan.usizes(k, 0);
        let dp_size = cap.iter().map(|x| x+1).product::<usize>();
        let mut dp = vec![-1i64; dp_size];
        let get_index = |indexes: &[usize]| {
            assert!(indexes.len() == k);
            assert!(indexes.iter().enumerate().all(|(i, x)| *x <= cap[i]));
            assert!(indexes.iter().enumerate().all(|(i, x)| i == 0 || indexes[i-1] >= *x));
            let mut plain_index = 0;
            let mut mult = 1;
            for i in (0..cap.len()).rev() {
                plain_index += indexes[i] * mult;
                mult *= cap[i]+1;
            }
            plain_index
        };

        let mut q = VecDeque::new();
        dp[get_index(&cap)] = 1;
        for i in 0..cap.len() {
            if i == cap.len()-1 || cap[i]-1 >= cap[i+1] {
                let mut state = cap.clone();
                state[i] -= 1;
                dp[get_index(&state)] = 0;
                q.push_back(state);
            }
        }

        while let Some(curr) = q.pop_front() {
            let idx = get_index(&curr);
            for i in 0..cap.len() {
                if curr[i]+1 <= cap[i] && (i == 0 || curr[i-1] >= curr[i]+1) {
                    let mut next = curr.clone();
                    next[i] += 1;
                    let next_dp = dp[get_index(&next)];
                    assert!(next_dp > 0, "{:#?} -> {:#?}", curr, next);
                    dp[idx] += next_dp;
                }
                if curr[i] == 0 {
                    break;
                }
            }
            for i in 0..cap.len() {
                if curr[i] > 0 && (i == cap.len()-1 || curr[i]-1 >= curr[i+1]) {
                    let mut prev = curr.clone();
                    prev[i] -= 1;
                    let prev_idx = get_index(&prev);
                    if dp[prev_idx] == -1 {
                        dp[prev_idx] = 0;
                        q.push_back(prev);
                    }
                }
            }
        }

        let init = vec![0; cap.len()];
        writeln!(writer, "{}", dp[get_index(&init)]).unwrap();
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
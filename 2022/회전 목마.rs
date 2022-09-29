use std::collections::VecDeque;

fn main() {
    let scan = &mut Scanner::default();
    let n = scan.usize();
    let arr = scan.i32s(n);
    let mut answer = usize::MAX;
    for i in 0..n {
        let arranged = arr
            .iter()
            .skip(i)
            .chain(arr.iter().take(i))
            .copied()
            .collect();
        answer = answer.min(get_cost(arranged));
    }

    println!("{answer}");
}

fn get_cost(mut arr: Vec<i32>) -> usize {
    let mut result = 0;
    let mut positive = VecDeque::new();
    let mut zero = VecDeque::new();
    for i in 0..arr.len() {
        while arr[i] > 1 && !zero.is_empty() {
            let pos = zero.pop_back().unwrap();
            arr[i] -= 1;
            arr[pos] += 1;
            result += i-pos;
        }
        if arr[i] > 1 {
            positive.push_back(i);
        } else if arr[i] == 0 {
            if let Some(pos) = positive.pop_back() {
                arr[pos] -= 1;
                arr[i] += 1;
                result += i-pos;
                if arr[pos] > 1 {
                    positive.push_back(pos);
                }
            } else {
                zero.push_back(i);
            }
        }
    }
    result
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
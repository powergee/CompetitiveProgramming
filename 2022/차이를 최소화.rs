use std::io::{BufWriter, stdout, Write};

fn main() {
    let io = &mut Scanner::default();
    
    let n: usize = io.next();
    let t: i32 = io.next();
    let arr: Vec<i32> = (0..n).map(|_| io.next()).collect();

    let is_possible = |max_diff: i32| -> Option<Vec<i32>> {
        let mut arr = arr.clone();
        let mut cost: i64 = 0;
        for i in 1..n {
            if arr[i-1]+max_diff < arr[i] {
                cost += (arr[i] - (arr[i-1]+max_diff)) as i64;
                arr[i] = arr[i-1]+max_diff;
            }
        }
        for i in (0..(n-1)).rev() {
            if arr[i+1]+max_diff < arr[i] {
                cost += (arr[i] - (arr[i+1]+max_diff)) as i64;
                arr[i] = arr[i+1]+max_diff;
            }
        }

        if cost <= t as i64 {
            Some(arr)
        } else {
            None
        }
    };

    let mut l = 0;
    let mut r = 1e9 as i32;
    let mut answer = vec![];
    while l < r {
        let m = (l+r) / 2;
        if let Some(result) = is_possible(m) {
            r = m;
            answer = result;
        } else {
            l = m+1;
        }
    }
    
    let mut out = BufWriter::new(stdout());
    for v in answer {
        write!(out, "{v} ").unwrap();
    }
    writeln!(out).unwrap();
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
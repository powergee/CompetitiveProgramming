use std::{collections::BTreeSet, io::{BufWriter, stdout}};
use std::io::Write;

fn main() {
    let scan = &mut Scanner::default();
    let n: i32 = scan.next();
    let mut has = BTreeSet::new();
    for _ in 0..n {
        let v: i32 = scan.next();
        has.insert(v);
    }

    let mut out = BufWriter::new(stdout());
    let m: i32 = scan.next();
    for _ in 0..m {
        let v: i32 = scan.next();
        if has.get(&v).is_some() {
            write!(out, "1 ").unwrap();
        } else {
            write!(out, "0 ").unwrap();
        }
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
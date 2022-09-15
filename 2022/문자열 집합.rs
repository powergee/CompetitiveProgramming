use std::{collections::BTreeSet};

fn main() {
    let scan = &mut Scanner::default();
    let n: i32 = scan.next();
    let m: i32 = scan.next();

    let has: BTreeSet<String> = (0..n).map(|_| scan.next()).collect();
    let query: Vec<String> = (0..m).map(|_| scan.next()).collect();
    let count = query.iter().filter(|&q| has.contains(q)).count();
    println!("{count}");
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
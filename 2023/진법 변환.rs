use std::io::{stdin, BufRead};

fn main() {
    let mut stdin = stdin().lock();
    let mut buf = String::default();
    stdin.read_line(&mut buf).unwrap();
    let mut iter = buf.trim().split_ascii_whitespace();
    let number = iter.next().unwrap().as_bytes();
    let base = iter.next().unwrap().parse::<usize>().unwrap();

    let mut result = 0;
    let mut mult = 1;
    let digits = (0..10)
        .map(|i| b'0' + i)
        .chain((0..26).map(|i| b'A' + i))
        .collect::<Vec<_>>();

    for n in number.iter().rev() {
        result += mult * digits.iter().enumerate().find(|&(_, d)| d == n).unwrap().0;
        mult *= base;
    }
    println!("{result}");
}

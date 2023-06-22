use std::io::{stdin, BufRead};

fn main() {
    let mut stdin = stdin().lock();
    let mut buf = String::default();
    stdin.read_line(&mut buf).unwrap();
    let mut iter = buf.trim().split_ascii_whitespace();
    let mut number = iter.next().unwrap().parse::<usize>().unwrap();
    let base = iter.next().unwrap().parse::<usize>().unwrap();

    let mut result = String::with_capacity(32);
    let digits = (0..10)
        .map(|i| b'0' + i)
        .chain((0..26).map(|i| b'A' + i))
        .collect::<Vec<_>>();

    while number > 0 {
        let digit = digits[number % base];
        result.push(digit as char);
        number /= base;
    }
    println!("{}", result.chars().rev().collect::<String>());
}

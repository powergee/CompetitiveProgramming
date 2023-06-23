use std::io::{stdin, BufRead};

fn main() {
    let mut stdin = stdin().lock();
    let mut buf = String::default();
    stdin.read_line(&mut buf).unwrap();
    let a = buf.trim().parse::<usize>().unwrap();
    buf.clear();
    stdin.read_line(&mut buf).unwrap();
    let b = buf.trim().parse::<usize>().unwrap();
    println!("{}", a * b);
}

use std::io::{stdin, BufRead};

fn main() {
    let mut buf = String::new();
    stdin().lock().read_line(&mut buf).unwrap();
    let n = buf.trim().parse::<usize>().unwrap();
    println!("{}", (n as f64).sqrt() as usize);
}

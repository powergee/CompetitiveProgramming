use std::io::{stdin, BufRead};

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let vs = buf
        .trim()
        .split_ascii_whitespace()
        .map(|tok| tok.parse::<usize>().unwrap())
        .collect::<Vec<_>>();
    let n = vs[4];
    let sum = vs.iter().take(4).sum::<usize>();
    println!("{}", (n * 4).checked_sub(sum).unwrap_or(0));
}

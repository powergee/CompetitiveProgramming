use std::io::stdin;

fn main() {
    let buf = &mut String::new();
    stdin().read_line(buf).unwrap();
    let vs = buf
        .trim()
        .split_ascii_whitespace()
        .map(|token| token.parse::<usize>().unwrap())
        .collect::<Vec<_>>();
    println!("{}{}", "1".repeat(vs[1] - 1), vs[0]);
}

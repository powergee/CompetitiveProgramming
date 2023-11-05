use std::io::{stdin, BufRead};

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let mut iter = buf
        .trim()
        .split_ascii_whitespace()
        .map(|token| token.parse::<u64>().unwrap());
    let n = iter.next().unwrap();
    let m = iter.next().unwrap();
    let mut level = 0;

    println!(
        "{}",
        loop {
            let min = (1 << level) * m - ((1 << level) - 1);
            let max = (1 << level) * m + ((1 << level) - 1);
            if n < min {
                break "NO";
            } else if min <= n && n <= max {
                break "YES";
            } else {
                level += 1;
            }
        }
    );
}

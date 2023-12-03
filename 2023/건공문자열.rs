use std::io::{stdin, BufRead};

fn main() {
    let mut stdin = stdin().lock();
    let (n, k) = {
        let buf = &mut String::new();
        stdin.read_line(buf).unwrap();
        let mut iter = buf
            .trim()
            .split_ascii_whitespace()
            .map(|tok| tok.parse::<usize>().unwrap());
        (iter.next().unwrap(), iter.next().unwrap())
    };
    let s = {
        let mut buf = String::new();
        stdin.read_line(&mut buf).unwrap();
        buf
    };
    let s = s.as_bytes();

    let mut answer = Vec::with_capacity(n);
    for i in 0..(n - k + 1) {
        answer.push(s[i + k - 1] as char);
    }
    for i in 0..(k - 1) {
        if (n - k) % 2 == 0 {
            answer.push(s[k - 2 - i] as char);
        } else {
            answer.push(s[i] as char);
        }
    }
    println!("{}", answer.into_iter().collect::<String>());
}

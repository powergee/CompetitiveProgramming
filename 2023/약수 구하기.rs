use std::io::{stdin, BufRead};

fn main() {
    let mut stdin = stdin().lock();
    let mut buf = String::default();
    stdin.read_line(&mut buf).unwrap();
    let mut iter = buf.trim().split_ascii_whitespace();
    let n = iter.next().unwrap().parse::<usize>().unwrap();
    let mut k = iter.next().unwrap().parse::<usize>().unwrap();

    let answer = 'answer: {
        for p in 1..=n {
            if n % p == 0 {
                k -= 1;
                if k == 0 {
                    break 'answer p;
                }
            }
        }
        0
    };

    println!("{answer}");
}

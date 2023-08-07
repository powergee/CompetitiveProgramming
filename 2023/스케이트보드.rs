use std::io::{stdin, BufRead};

fn main() {
    let stdin = &mut stdin().lock();

    let n = {
        let buf = &mut String::new();
        stdin.read_line(buf).unwrap();
        buf.trim().parse::<usize>().unwrap()
    };

    let mut winner = 0;
    for _ in 0..n {
        let mut scores = {
            let buf = &mut String::new();
            stdin.read_line(buf).unwrap();
            buf.trim()
                .split_ascii_whitespace()
                .map(|token| token.parse::<usize>().unwrap())
                .collect::<Vec<_>>()
        };
        scores[2..].sort();
        winner = winner.max(scores[0].max(scores[1]) + scores[5] + scores[6]);
    }

    println!("{winner}");
}

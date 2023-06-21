use std::io::{stdin, BufRead};

fn main() {
    let mut stdin = stdin().lock();
    let mut total = 0.0;
    let mut count = 0.0;

    for _ in 0..20 {
        let mut buf = String::default();
        stdin.read_line(&mut buf).unwrap();
        let mut iter = buf.trim().split_ascii_whitespace();
        let _ = iter.next().unwrap();
        let credit = iter.next().unwrap().parse::<f64>().unwrap();
        let score = iter.next().unwrap();

        if score == "P" {
            continue;
        }

        let score = match score {
            "A+" => 4.5,
            "A0" => 4.0,
            "B+" => 3.5,
            "B0" => 3.0,
            "C+" => 2.5,
            "C0" => 2.0,
            "D+" => 1.5,
            "D0" => 1.0,
            "F" => 0.0,
            _ => unreachable!(),
        };

        total += credit * score;
        count += credit;
    }

    println!("{:.}", total / count);
}

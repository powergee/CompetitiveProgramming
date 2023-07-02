use std::io::{stdin, BufRead};

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let mut iter = buf
        .trim()
        .split_ascii_whitespace()
        .map(|s| s.parse::<f64>().unwrap());
    let (x, y, d, t) = (
        iter.next().unwrap(),
        iter.next().unwrap(),
        iter.next().unwrap(),
        iter.next().unwrap(),
    );

    let dist = ((x * x) + (y * y)).sqrt();
    let cands = [
        dist,
        {
            let jump_dist = (dist / d).floor() * d;
            let jump_time = (dist / d).floor() * t;
            jump_time + (dist - jump_dist).abs()
        },
        {
            let jump_dist = (dist / d).ceil() * d;
            let jump_time = (dist / d).ceil() * t;
            jump_time + (dist - jump_dist).abs()
        },
        if (dist / d).ceil() >= 2.0 {
            (dist / d).ceil() * t
        } else {
            2.0 * t
        }
    ];
    println!("{:.10}", cands.iter().fold(f64::MAX, |min, c| min.min(*c)));
}

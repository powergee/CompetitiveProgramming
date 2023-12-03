use std::io::{stdin, BufRead};

fn main() {
    let n = {
        let buf = &mut String::new();
        stdin().lock().read_line(buf).unwrap();
        buf.trim().parse::<u64>().unwrap()
    };

    let mut answer = 1u64;
    for i in 0..5 {
        answer *= n - i;
    }
    for i in 1..=5 {
        answer /= i;
    }

    println!("{answer}");
}

use std::io::{stdin, BufRead};

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let mut io = buf.trim().split_ascii_whitespace();
    let r1 = io.next().unwrap().parse::<i32>().unwrap();
    let c1 = io.next().unwrap().parse::<i32>().unwrap();
    let r2 = io.next().unwrap().parse::<i32>().unwrap();
    let c2 = io.next().unwrap().parse::<i32>().unwrap();

    let answer = (r1..=r2)
        .map(|r| {
            (c1..=c2)
                .map(|c| value(r, c).to_string())
                .collect::<Vec<_>>()
        })
        .collect::<Vec<_>>();

    let max_width = answer
        .iter()
        .flat_map(|s| s.iter())
        .fold(0, |max, s| max.max(s.len()));

    println!(
        "{}",
        answer
            .into_iter()
            .map(|s| s
                .into_iter()
                .map(|s| format!("{: >width$}", s, width = max_width))
                .collect::<Vec<String>>()
                .join(" "))
            .collect::<Vec<String>>()
            .join("\n")
    )
}

fn value(r: i32, c: i32) -> i32 {
    let n = r.abs_diff(0).max(c.abs_diff(0)) as i32;
    let result = (2 * n + 1) * (2 * n + 1);

    if r == n {
        result - c.abs_diff(n) as i32
    } else if c == -n {
        result - 2 * n - r.abs_diff(n) as i32
    } else if r == -n {
        result - 4 * n - c.abs_diff(-n) as i32
    } else {
        result - 6 * n - r.abs_diff(-n) as i32
    }
}

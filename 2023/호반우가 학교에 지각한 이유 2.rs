use std::{
    collections::VecDeque,
    io::{stdin, BufRead},
};

const GRAPH: &'static [&'static [usize]] = &[
    &[2, 3, 5, 7],
    &[1, 3, 7, 9],
    &[3, 9],
    &[1, 7],
    &[1, 3, 7],
    &[3, 9],
    &[1, 7],
    &[1, 3, 9],
    &[3, 9],
    &[7],
];

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let mut toks = buf
        .trim()
        .split_ascii_whitespace()
        .map(|tok| tok.parse::<usize>().unwrap());
    let a = toks.next().unwrap();
    let b = toks.next().unwrap();
    let n = toks.next().unwrap();

    // prev[vertex][dist]
    let mut prev = [[None; 100]; 10];
    prev[a % 10][0] = Some(a / 10);
    let mut q = VecDeque::new();
    q.push_back((a % 10, 0));
    while let Some((v, d)) = q.pop_front() {
        for &next in GRAPH[v] {
            if d + 1 < 100 && prev[next][d + 1].is_none() {
                prev[next][d + 1] = Some(v);
                q.push_back((next, d + 1));
            }
        }
    }

    let dst = b / 10;
    if prev[dst][n - 3].is_none() {
        println!("-1");
        return;
    }

    let mut buf = Vec::with_capacity(n);
    buf.push(((b % 10) as u8 + b'0') as char);
    buf.push(((b / 10) as u8 + b'0') as char);
    let mut u = dst;
    for dist in (0..n - 2).rev() {
        u = prev[u][dist].unwrap();
        buf.push((u as u8 + b'0') as char);
    }
    println!("{}", buf.into_iter().rev().collect::<String>());
}

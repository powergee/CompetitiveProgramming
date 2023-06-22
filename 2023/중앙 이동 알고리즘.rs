use std::io::{stdin, BufRead};

fn main() {
    let mut stdin = stdin().lock();
    let mut buf = String::default();
    stdin.read_line(&mut buf).unwrap();
    let n = buf.trim().parse::<usize>().unwrap();

    let part_cnt = 1 << n;
    let points_on_a_side = part_cnt + 1;
    let points = points_on_a_side * points_on_a_side;
    println!("{points}")
}

use std::io::stdin;

const MOD: i64 = 1000000000;

fn main() {
    let buf = &mut String::new();
    stdin().read_line(buf).unwrap();
    let n = buf.trim().parse::<i64>().unwrap();
    let mut prev = 1;
    let mut sub = 1;
    for i in 1..n + 1 {
        sub *= -1;
        prev = (i * prev + sub + MOD) % MOD;
    }
    println!("{prev}")
}

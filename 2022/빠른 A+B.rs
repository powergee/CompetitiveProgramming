use std::io;
use std::io::Write;

fn main() {
    let stdout = io::stdout();
    let mut out = io::BufWriter::new(stdout.lock());

    let mut line = String::new();
    io::stdin()
        .read_line(&mut line)
        .unwrap();
    let n: i32 = line.trim().parse().unwrap();
    
    for _ in 0..n {
        let mut line = String::new();
        io::stdin()
            .read_line(&mut line)
            .unwrap();
        let tokens: Vec<&str> = line
            .trim()
            .split(" ")
            .collect();
        let a: i32 = tokens[0].trim().parse().unwrap();
        let b: i32 = tokens[1].trim().parse().unwrap();
        writeln!(out, "{}", a+b).unwrap();
    }
}
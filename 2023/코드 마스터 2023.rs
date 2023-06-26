use std::io::{stdin, BufRead};

fn main() {
    let mut line = String::new();
    stdin().lock().read_line(&mut line).unwrap();
    let answer = match line.trim() {
        "SONGDO" => "HIGHSCHOOL",
        "CODE" => "MASTER",
        "2023" => "0611",
        "ALGORITHM" => "CONTEST",
        _ => unreachable!(),
    };
    println!("{answer}");
}

use std::io::{stdin, BufRead};

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let str = buf.trim();
    const KOREA: [char; 5] = ['K', 'O', 'R', 'E', 'A'];
    let mut i = 0;
    let mut matched = 0;
    for ch in str.chars() {
        if KOREA[i] == ch {
            matched += 1;
            i += 1;
            i %= 5;
        }
    }
    println!("{matched}");
}

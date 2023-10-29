use std::io::stdin;

fn main() {
    println!(
        "{}",
        (0..15)
            .map(|_| {
                let line = &mut String::new();
                stdin().read_line(line).unwrap();
                line.trim().to_string()
            })
            .fold(None, |found: Option<&'static str>, line| {
                if found.is_some() {
                    return found;
                }
                for ch in line.chars() {
                    match ch {
                        'w' => return Some("chunbae"),
                        'b' => return Some("nabi"),
                        'g' => return Some("yeongcheol"),
                        _ => continue,
                    }
                }
                None
            })
            .unwrap()
    );
}

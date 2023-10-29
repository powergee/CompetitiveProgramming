use std::io::{stdin, BufRead};

const LOWER: &'static str = "roygbiv";
const UPPER: &'static str = "ROYGBIV";

fn main() {
    let lines = &mut stdin().lock().lines();
    let _ = lines.next();
    let input = lines.next().unwrap().unwrap();

    let mut lower_app = vec![false; LOWER.len()];
    let mut upper_app = vec![false; UPPER.len()];

    for ch in input.chars() {
        if let Some(idx) = LOWER.find(ch) {
            lower_app[idx] = true;
        }
        if let Some(idx) = UPPER.find(ch) {
            upper_app[idx] = true;
        }
    }

    let lower = lower_app.into_iter().all(|app| app);
    let upper = upper_app.into_iter().all(|app| app);
    if lower && upper {
        println!("YeS");
    } else if lower {
        println!("yes");
    } else if upper {
        println!("YES");
    } else {
        println!("NO!");
    }
}

use std::{
    collections::BTreeMap,
    io::{stdin, BufRead},
};

fn main() {
    let s = {
        let mut buf = String::new();
        let stdin = &mut stdin().lock();
        stdin.read_line(&mut buf).unwrap();
        buf.clear();
        stdin.read_line(&mut buf).unwrap();
        buf
    };

    let mut count = BTreeMap::new();
    for ch in s.chars() {
        match ch {
            'u' | 'o' | 's' | 'p' | 'c' => *count.entry(ch).or_insert(0) += 1,
            _ => {}
        }
    }

    let answer = if count.len() == 5 {
        count.into_iter().map(|(_, cnt)| cnt).min().unwrap()
    } else {
        0
    };
    println!("{answer}");
}

use std::{collections::BTreeSet};

fn main() {
    let mut input = String::new();
    std::io::stdin().read_line(&mut input).unwrap();
    let input = input.trim();

    let mut set = BTreeSet::new();
    for i in 0..input.len() {
        for j in i..input.len() {
            let sub = input[i..(j+1)].to_string();
            set.insert(sub);
        }
    }
    println!("{}", set.len());
}
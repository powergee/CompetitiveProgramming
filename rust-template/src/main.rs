#![allow(unused)]
use std::io::{read_to_string, stdin, stdout, BufWriter, Write};
use std::str::{FromStr, SplitAsciiWhitespace};

fn main() {
    let mut input = In::stdin();
    let mut writer = BufWriter::new(stdout().lock());
}

struct In(SplitAsciiWhitespace<'static>);

impl In {
    fn stdin() -> Self {
        let iter = read_to_string(stdin().lock())
            .map(|buf| buf.leak().trim().split_ascii_whitespace())
            .unwrap();
        Self(iter)
    }

    fn read<T: FromStr>(&mut self) -> T {
        self.0.next().and_then(|s| s.parse::<T>().ok()).unwrap()
    }
}

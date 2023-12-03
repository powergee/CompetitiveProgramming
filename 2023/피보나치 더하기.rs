use std::collections::HashMap;

macro_rules! some_or {
    ($e:expr, $err:expr) => {{
        match $e {
            Some(r) => r,
            None => $err,
        }
    }};
}

fn main() {
    let mut input = In::stdin();

    let t = input.read::<usize>();
    let mut answers = vec![false; t];
    let mut queries = [HashMap::new(), HashMap::new(), HashMap::new()];

    for i in 0..t {
        let k = input.read::<usize>();
        let x = input.read::<u64>();
        queries[k - 1].entry(x).or_insert(vec![]).push(i);
    }

    let mut pr1 = 1u64;
    let mut pr2 = 1;
    let mut fibo = vec![pr1, pr2];
    while let Some(next) = pr1.checked_add(pr2) {
        fibo.push(next);
        pr1 = pr2;
        pr2 = next;
    }

    for i in 0..fibo.len() {
        let sum = fibo[i];
        if let Some(qs) = queries[0].get(&sum) {
            qs.iter().for_each(|q| answers[*q] = true);
        }
        for j in 0..fibo.len() {
            let sum = some_or!(sum.checked_add(fibo[j]), break);
            if let Some(qs) = queries[1].get(&sum) {
                qs.iter().for_each(|q| answers[*q] = true);
            }
            for k in 0..fibo.len() {
                let sum = some_or!(sum.checked_add(fibo[k]), break);
                if let Some(qs) = queries[2].get(&sum) {
                    qs.iter().for_each(|q| answers[*q] = true);
                }
            }
        }
    }
    println!(
        "{}",
        answers
            .into_iter()
            .map(|t| if t { "YES" } else { "NO" }.to_string())
            .collect::<Vec<String>>()
            .join("\n")
    );
}

struct In(std::str::SplitAsciiWhitespace<'static>, String);

impl In {
    fn stdin() -> Self {
        let buf = std::io::read_to_string(std::io::stdin().lock()).unwrap();
        let iter = unsafe { std::mem::transmute(buf.trim().split_ascii_whitespace()) };
        Self(iter, buf)
    }

    fn read<T: std::str::FromStr + std::fmt::Debug>(&mut self) -> T {
        self.0.next().and_then(|s| s.parse::<T>().ok()).unwrap()
    }
}

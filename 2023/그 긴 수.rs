use std::io::{stdin, BufRead};

macro_rules! some_or {
    ($e:expr, $err:expr) => {{
        match $e {
            Some(r) => r,
            None => $err,
        }
    }};
}

fn main() {
    let mut group_lens = vec![0, 9];
    for l in 2.. {
        let mut count = some_or!(count_nums(l / 2 + l % 2), break);
        count = some_or!(count.checked_mul(l as _), break);
        group_lens.push(group_lens.last().unwrap() + count);
    }

    let k = {
        let buf = &mut String::new();
        stdin().lock().read_line(buf).unwrap();
        buf.trim().parse::<u64>().unwrap()
    };
    println!("{}", solve(&group_lens, k));
}

fn solve(group_lens: &Vec<u64>, k: u64) -> char {
    for (l, &len) in group_lens.iter().enumerate().skip(1) {
        if k > len {
            continue;
        }
        if l == 1 {
            return k.to_string().chars().next().unwrap();
        } else {
            let num_idx = (k - group_lens[l - 1] - 1) / (l as u64);
            let half = (10u64.pow((l / 2 + l % 2) as u32 - 1) + num_idx).to_string();
            let num = if l % 2 == 0 {
                let temp = half.chars().rev().collect::<String>();
                half + &temp
            } else {
                let temp = half.chars().take(l / 2).collect::<Vec<_>>();
                half + &temp.into_iter().rev().collect::<String>()
            };
            let digits = num.chars().collect::<Vec<_>>();
            return digits[((k - group_lens[l - 1] - 1) % (l as u64)) as usize];
        }
    }
    unreachable!()
}

fn count_nums(digits: u32) -> Option<u64> {
    if digits == 1 {
        Some(9)
    } else {
        Some(10u64.checked_pow(digits)? - 10u64.checked_pow(digits - 1)?)
    }
}

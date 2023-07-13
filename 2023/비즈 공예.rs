use std::{collections::HashMap, io::stdin, iter::repeat};

fn main() {
    let count = {
        let n = read() as usize;
        (0..n)
            .map(|_| read())
            .chain(repeat(0).take(5 - n))
            .collect::<Vec<_>>()
    };

    let mut dp: HashMap<Vec<u8>, u64> = HashMap::new();
    for i in 0..5 {
        for j in 0..5 {
            if i != j {
                let mut state = Vec::with_capacity(7);
                state.push(i);
                state.push(j);
                state.extend(repeat(0).take(5));
                dp.insert(state, 1);
            }
        }
    }

    let mut remains = vec![];
    for r1 in 0..=count[0] {
        for r2 in 0..=count[1] {
            for r3 in 0..=count[2] {
                for r4 in 0..=count[3] {
                    for r5 in 0..=count[4] {
                        remains.push(vec![r1, r2, r3, r4, r5])
                    }
                }
            }
        }
    }
    remains.sort_unstable_by(|r1, r2| {
        r1.iter()
            .copied()
            .sum::<u8>()
            .cmp(&r2.iter().copied().sum::<u8>())
    });

    for rem in remains.into_iter().skip(1) {
        for i in 0..5 {
            for j in 0..5 {
                if i == j {
                    continue;
                }
                let mut state = Vec::with_capacity(7);
                state.push(i as u8);
                state.push(j as u8);
                state.append(&mut rem.clone());
                let mut total = 0;
                for (k, &r) in rem.iter().enumerate() {
                    if r == 0 || i == k || j == k {
                        continue;
                    }
                    let mut next = state.clone();
                    next[0] = next[1];
                    next[1] = k as u8;
                    next[2 + k] -= 1;
                    total += dp.get(&next).unwrap();
                }
                dp.insert(state, total);
            }
        }
    }

    let mut answer = 0;
    for i in 0..5 {
        for j in 0..5 {
            if i != j && count[i] > 0 && count[j] > 0 {
                let mut state = Vec::with_capacity(7);
                state.push(i as u8);
                state.push(j as u8);
                state.append(&mut count.clone());
                state[2 + i] -= 1;
                state[2 + j] -= 1;
                answer += dp.get(&state).unwrap();
            }
        }
    }

    println!("{answer}");
}

fn read() -> u8 {
    let buf = &mut String::new();
    stdin().read_line(buf).unwrap();
    buf.trim().parse::<u8>().unwrap()
}

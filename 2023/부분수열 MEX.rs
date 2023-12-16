use std::io::{stdin, BufRead};

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let num = buf
        .trim()
        .chars()
        .into_iter()
        .map(|ch| ch as u8 - b'0')
        .collect::<Vec<_>>();
    let n = num.len();
    let mut nearest: Vec<[usize; 10]> = vec![[0; 10]; num.len()];
    nearest[n - 1] = [n; 10];
    nearest[n - 1][num[n - 1] as usize] = n - 1;

    for i in (0..n - 1).rev() {
        nearest[i] = nearest[i + 1].clone();
        nearest[i][num[i] as usize] = i;
    }

    // pair: (length of the resulting seq, current selection)
    let mut dp = vec![(0, 0); n + 1];
    dp[n] = (1, 0);
    for i in (0..n).rev() {
        let mut cands = [(0, 0); 10];
        let range = if i == 0 { 1..10 } else { 0..10 };
        for v in range.clone() {
            let near = nearest[i][v];
            let cand = if let Some((nl, _)) = dp.get(near + 1) {
                (1 + nl, v)
            } else {
                (1, v)
            };
            cands[v] = cand;
        }
        dp[i] = range.map(|v| cands[v]).min().unwrap();
    }

    let mut answer = Vec::with_capacity(dp[0].0);
    let mut cursor = 0;
    loop {
        let (len, sel) = dp[cursor];
        answer.push(sel as u8 + b'0');
        if len == 1 {
            break;
        }
        cursor = nearest[cursor][sel] + 1;
    }
    println!("{}", unsafe { String::from_utf8_unchecked(answer) });
}

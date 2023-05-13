fn main() {
    let mut buf = String::new();
    std::io::stdin().read_line(&mut buf).unwrap();
    let cap: [usize; 3] = buf
        .trim()
        .split(' ')
        .map(|tok| tok.parse().unwrap())
        .collect::<Vec<_>>()
        .try_into()
        .unwrap();

    let mut visited = [[[false; 201]; 201]; 201];
    visited[0][0][cap[2]] = true;
    let mut q = Vec::new();
    q.push([0, 0, cap[2]]);

    while let Some(amount) = q.pop() {
        for (i, j) in (0..9).map(|i| (i / 3, i % 3)).filter(|(i, j)| i != j) {
            let mut next = amount.clone();
            if amount[i] <= cap[j] - amount[j] {
                (next[i], next[j]) = (0, amount[i] + amount[j]);
            } else {
                (next[i], next[j]) = (amount[i] - (cap[j] - amount[j]), cap[j]);
            }
            if !visited[next[0]][next[1]][next[2]] {
                visited[next[0]][next[1]][next[2]] = true;
                q.push(next);
            }
        }
    }

    let mut answer = [false; 201];
    for b in 0..=cap[1] {
        for c in 0..=cap[2] {
            if visited[0][b][c] {
                answer[c] = true;
            }
        }
    }

    println!(
        "{}",
        answer
            .iter()
            .zip(0..201)
            .filter_map(|(exist, i)| {
                if *exist {
                    Some(i.to_string())
                } else {
                    None
                }
            })
            .collect::<Vec<_>>()
            .join(" ")
    );
}

use std::io::BufRead;

fn main() {
    let mut line = String::new();
    std::io::stdin().lock().read_line(&mut line).unwrap();
    let mut tokens = line.split_ascii_whitespace();
    let n: usize = tokens.next().unwrap().parse().unwrap();
    let k: usize = tokens.next().unwrap().parse().unwrap();

    let mut dist = vec![usize::MAX; n + n / 2 + 2];
    dist[0] = 0;
    for i in 0..n + 1 {
        for next_idx in [i + 1, i + i / 2] {
            dist[next_idx] = dist[next_idx].min(dist[i] + 1);
        }
    }
    println!(
        "{}",
        if dist[n] <= k {
            "minigimbob"
        } else {
            "water"
        }
    )
}

use std::io::{stdin, BufRead};

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let line = buf.trim().as_bytes();
    
    let mut dp = vec![vec![0; line.len()]; line.len()];
    for i in 0..line.len() {
        dp[i][i] = 1;
    }
    for i in 0..line.len() - 1 {
        dp[i][i + 1] = 2 + if line[i] == line[i+1] { 1 } else { 0 };
    }
    for k in 2..line.len() {
        for i in 0..line.len()-k {
            let j = i + k;
            dp[i][j] = dp[i][j-1] + dp[i+1][j] - dp[i+1][j-1];
            if line[i] == line[j] {
                dp[i][j] += dp[i+1][j-1] + 1;
            }
        }
    }
    println!("{}", dp[0][line.len() - 1]);
}

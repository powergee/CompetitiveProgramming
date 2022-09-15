fn main() {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).unwrap();
    let n: usize = line.trim().parse().unwrap();

    let mut dp = [[0u64; 13]; 100000];
    for d in 2..=10 {
        dp[0][d] = 1u64;
    }
    for i in 1..n {
        for d in 2..=10 {
            dp[i][d] = (dp[i-1][d-2] + dp[i-1][d-1] + dp[i-1][d] + dp[i-1][d+1] + dp[i-1][d+2]) % 987654321;
        }
    }

    let mut answer = 0u64;
    for d in 2..=10 {
        answer += dp[n-1][d];
        answer %= 987654321;
    }

    println!("{}", answer);
}
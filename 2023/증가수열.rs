fn main() {
    let mut str = String::new();
    std::io::stdin().read_line(&mut str).unwrap();
    let str = str.trim();
    let mut dp = vec![vec![false; str.len()]; str.len()];

    for i in 0..str.len() {
        dp[0][i] = true;
    }
    // dp[i][j] = OR { dp[k][i-1] & str[k..=i-1] < str[i..=j] }
    for j in 1..str.len() {
        for i in (1..=j).rev() {
            for k in (0..=i - 1).rev() {
                if !gt_as_num(&str[k..=i - 1], &str[i..=j]) {
                    break;
                }
                if dp[k][i - 1] {
                    dp[i][j] = true;
                    break;
                }
            }
        }
    }

    for i in (0..str.len()).rev() {
        if dp[i][str.len() - 1] {
            let result = (&str[i..=str.len() - 1]).trim_start_matches('0');
            if result.len() == 0 {
                println!("0");
            } else {
                println!("{}", result);
            }
            break;
        }
    }
}

fn gt_as_num(a: &str, b: &str) -> bool {
    let a = a.trim_start_matches('0');
    let b = b.trim_start_matches('0');

    if a.len() != b.len() {
        a.len() < b.len()
    } else {
        a < b
    }
}

use std::io::{stdout, BufWriter, Write};

static mut DP: [[[u16; 512]; 500]; 500] = [[[0; 512]; 500]; 500];

fn main() {
    let mut input = In::stdin();
    let n = input.read::<usize>();
    let ts = (0..n).map(|_| input.read::<usize>()).collect::<Vec<_>>();

    let dp = unsafe { &mut DP };
    for l in 0..n {
        dp[l][l][ts[l]] = 1;
        for r in l + 1..n {
            dp[l][r][ts[r]] = 1;
            for goal in 0..512 {
                dp[l][r][goal] = dp[l][r][goal].max(dp[l][r - 1][goal]);
                if dp[l][r - 1][goal ^ ts[r]] > 0 {
                    dp[l][r][goal] = dp[l][r][goal].max(dp[l][r - 1][goal ^ ts[r]] + 1);
                }
            }
        }
    }

    let mut writer = BufWriter::new(stdout().lock());
    for _ in 0..input.read::<usize>() {
        let l = input.read::<usize>() - 1;
        let r = input.read::<usize>() - 1;
        let answer = dp[l][r]
            .iter()
            .enumerate()
            .filter_map(|(goal, count)| {
                if *count == 0 {
                    None
                } else {
                    Some(goal as u16 + count)
                }
            })
            .max()
            .unwrap();
        writeln!(writer, "{answer}").unwrap();
    }
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

use std::io::stdin;

fn main() {
    let buf = &mut String::new();
    stdin().read_line(buf).unwrap();
    let n = buf.trim().parse::<u32>().unwrap();
    let mut dp = vec![false; n as usize + 1];

    let mut last_succ = None;
    for curr in 10..n + 1 {
        let mut succ = u32::MAX;
        for sub in SubNumberIterator::new(curr) {
            if sub != 0 && sub < succ && !dp[(curr - sub) as usize] {
                succ = succ.min(sub);
            }
        }
        if succ == u32::MAX {
            dp[curr as usize] = false;
            last_succ = None;
        } else {
            dp[curr as usize] = true;
            last_succ = Some(succ);
        }
    }

    if let Some(answer) = last_succ {
        println!("{}", answer);
    } else {
        println!("-1");
    }
}

struct SubNumberIterator {
    origin: u32,
    upper: u32,
    lower: u32,
}

impl SubNumberIterator {
    fn new(origin: u32) -> Self {
        assert!(origin >= 10);
        let mut upper = 1;
        while upper <= origin {
            upper *= 10;
        }
        Self {
            origin,
            upper,
            lower: 10, // skip the origin itself
        }
    }
}

impl Iterator for SubNumberIterator {
    type Item = u32;

    fn next(&mut self) -> Option<Self::Item> {
        if self.upper == 1 {
            return None;
        }
        let result = (self.origin % self.upper) / self.lower;
        self.lower *= 10;
        if self.lower == self.upper {
            self.upper /= 10;
            self.lower = 1;
        }
        Some(result)
    }
}

use std::io::stdin;

fn main() {
    let (s1, s2, s3) = (&mut String::new(), &mut String::new(), &mut String::new());
    stdin().read_line(s1).unwrap();
    stdin().read_line(s2).unwrap();
    stdin().read_line(s3).unwrap();

    let (s1, s2, s3) = (
        s1.trim().as_bytes(),
        s2.trim().as_bytes(),
        s3.trim().as_bytes(),
    );
    let dp = vec![vec![vec![None; s3.len()]; s2.len()]; s1.len()];
    let mut state = State { s1, s2, s3, dp };
    println!("{}", state.lcs(0, 0, 0));
}

struct State<'s> {
    s1: &'s [u8],
    s2: &'s [u8],
    s3: &'s [u8],
    dp: Vec<Vec<Vec<Option<u32>>>>,
}

impl<'s> State<'s> {
    fn lcs(&mut self, i1: usize, i2: usize, i3: usize) -> u32 {
        if i1 >= self.s1.len() || i2 >= self.s2.len() || i3 >= self.s3.len() {
            return 0;
        }
        if let Some(lcs) = self.dp[i1][i2][i3] {
            return lcs;
        }

        let mut result = *[
            self.lcs(i1 + 1, i2, i3),
            self.lcs(i1, i2 + 1, i3),
            self.lcs(i1, i2, i3 + 1),
        ]
        .iter()
        .max()
        .unwrap();

        if self.s1[i1] == self.s2[i2] && self.s2[i2] == self.s3[i3] {
            result = result.max(1 + self.lcs(i1 + 1, i2 + 1, i3 + 1))
        }
        *self.dp[i1][i2][i3].insert(result)
    }
}

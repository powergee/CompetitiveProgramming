fn main() {
    let ans = solve()
        .map(|ans| ans.to_string())
        .unwrap_or("-1".to_string());
    println!("{}", ans);
}

fn solve() -> Option<usize> {
    let mut input = In::stdin();
    let n = input.read::<usize>();
    let mut pos = vec![(0, 0); 2 * n];
    let mut rows = vec![[2 * n; 2]; n];
    let mut cols = vec![[2 * n; 2]; n];

    for i in 0..2 * n {
        pos[i] = (input.read::<usize>() - 1, input.read::<usize>() - 1);
        push(&mut rows[pos[i].0], i, 2 * n)?;
        push(&mut cols[pos[i].1], i, 2 * n)?;
    }

    let mut total_diffs = 0;
    let mut visited = vec![false; 2 * n];
    for i in 0..2 * n {
        if visited[i] {
            continue;
        }
        let mut q = Vec::new();
        let mut colors = Vec::new();
        q.push((i, false));
        colors.push((i, false));
        visited[i] = true;

        while let Some((u, curr_color)) = q.pop() {
            let (r, c) = pos[u];
            for &v in rows[r].iter().chain(cols[c].iter()) {
                if !visited[v] {
                    let next_color = !curr_color;
                    visited[v] = true;
                    q.push((v, next_color));
                    colors.push((v, next_color));
                }
            }
        }

        let count = colors.len();
        let diff = colors
            .into_iter()
            .map(|(u, color)| if color == (u < n) { 1 } else { 0 })
            .sum::<usize>();
        total_diffs += diff.min(count - diff);
    }

    assert!(total_diffs % 2 == 0);
    Some(total_diffs / 2)
}

fn push<const S: usize>(arr: &mut [usize; S], v: usize, inv: usize) -> Option<()> {
    for slot in arr {
        if *slot == inv {
            *slot = v;
            return Some(());
        }
    }
    None
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

fn main() {
    let mut input = In::stdin();
    let (n, k) = (input.read::<usize>(), input.read::<usize>());
    let mut meetings = (0..n)
        .map(|_| (input.read::<u32>(), input.read::<u32>()))
        .collect::<Vec<_>>();
    meetings.sort_by_key(|x| (x.1, x.0));
    let mut rooms = vec![0; k];

    let mut answer = 0;
    for (s, e) in meetings {
        let assign = rooms.iter_mut().filter(|r| **r < s).max();
        if let Some(r) = assign {
            *r = e;
            answer += 1;
        }
    }
    println!("{answer}");
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

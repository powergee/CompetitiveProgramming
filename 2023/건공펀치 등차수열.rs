fn main() {
    let mut input = In::stdin();
    let (n, k) = (input.read::<usize>(), input.read::<i64>());
    let arr = (0..n).map(|_| input.read::<i64>()).collect::<Vec<_>>();
    let mut max_base = *arr.first().unwrap();

    for i in 1..n {
        let curr_base = arr[i] - i as i64 * k;
        if max_base < curr_base {
            max_base = curr_base;
        }
    }

    let mut answer = 0;
    for i in 0..n {
        answer += (max_base + k * i as i64) - arr[i];
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

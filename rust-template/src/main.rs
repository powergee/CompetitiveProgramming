#![allow(unused)]
macro_rules! some_or {
    ($e:expr, $err:expr) => {{
        match $e {
            Some(r) => r,
            None => $err,
        }
    }};
}

fn main() {
    let mut input = In::stdin();
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

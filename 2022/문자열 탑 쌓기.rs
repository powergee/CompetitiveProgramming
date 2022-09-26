fn main() {
    let scan = &mut Scanner::default();
    let (n, _) = (scan.usize(), scan.usize());
    let words: Vec<_> = (0..n).map(|_| scan.string()).collect();
    let mut result = 1;
    for i in 1..n {
        if !mergable(&words[i-1], &words[i]) {
            result = 0;
            break;
        }
    }
    println!("{}", result)
}

fn mergable(s: &String, t: &String) -> bool {
    assert!(s.len() == t.len());
    let m = s.len();
    // t left == s right
    for i in 0..m {
        if t[0..=i] == s[m-i-1..m] {
            return true;
        }
    }
    // s left == t right
    for i in 0..m {
        if s[0..=i] == t[m-i-1..m] {
            return true;
        }
    }
    return false;
}

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            std::io::stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

macro_rules! scanner_shortcut {
    ($scan_type:ident) => {
        impl Scanner {
            #[allow(unused)]
            fn $scan_type(&mut self) -> $scan_type {
                self.next()
            }
        }
    };
    ($method_name:ident, $scan_type:ident) => {
        impl Scanner {
            #[allow(unused)]
            fn $method_name(&mut self) -> $scan_type {
                self.next()
            }
        }
    };
}
scanner_shortcut!(i32);
scanner_shortcut!(i64);
scanner_shortcut!(isize);
scanner_shortcut!(u32);
scanner_shortcut!(u64);
scanner_shortcut!(usize);
scanner_shortcut!(string, String);
fn main() {
    let scan = &mut Scanner::default();
    let mine = scan.string();
    let n = scan.i32();
    let s: i32 = (0..n).map(|_| {
        let other = scan.string();
        if other == mine { 1 } else { 0 }
    }).sum();
    println!("{}", s);
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
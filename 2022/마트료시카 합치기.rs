fn main() {
    let scan = &mut Scanner::default();
    let n = scan.usize();
    let mut dolls = (0..n).map(|_| scan.i32()).collect::<Vec<_>>();
    dolls.sort();
    let mut buckets: Vec<i32> = vec![];
    for v in dolls {
        let mut found = false;
        for b in &mut buckets {
            if *b < v {
                *b = v;
                found = true;
                break;
            }
        }
        if !found {
            buckets.push(v);
        }
    }

    println!("{}", buckets.len())
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
}
scanner_shortcut!(i32);
scanner_shortcut!(i64);
scanner_shortcut!(isize);
scanner_shortcut!(u32);
scanner_shortcut!(u64);
scanner_shortcut!(usize);
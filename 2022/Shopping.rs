fn main() {
    let scan = &mut Scanner::default();
    let (n, m) = (scan.i32(), scan.usize());

    if m == 0 {
        println!("{}", n+1);
        return;
    }

    let mut intervals = (0..m).map(|_| (scan.i32(), scan.i32())).collect::<Vec<_>>();
    intervals.sort();
    
    let mut answer = 0;
    let mut acc = intervals.first().unwrap().clone();
    for i in 1..m {
        let curr = intervals[i].clone();
        if curr.0 <= acc.1 {
            acc.1 = std::cmp::max(curr.1, acc.1);
        } else {
            answer += (acc.1-acc.0)*2;
            acc = curr;
        }
    }
    answer += (acc.1-acc.0)*2 + n+1;
    println!("{}", answer);
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
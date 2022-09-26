fn main() {
    let scan = &mut Scanner::default();
    let expr = scan.next::<String>();
    let bob = scan.u32();

    let expr = expr.as_bytes().iter().map(|b| b.clone() as char).collect::<Vec<char>>();
    
    let mult = multiplication_first(expr.clone());
    let left = left_to_right(expr.clone());
    
    let answer = if mult == bob && left == bob {
        'U'
    } else if mult == bob {
        'M'
    } else if left == bob {
        'L'
    } else {
        'I'
    };
    println!("{}", answer);
}

fn multiplication_first(expr: Vec<char>) -> u32 {
    let mut num_q: Vec<u32> = Vec::new();
    let mut i = 0;
    while i < expr.len() {
        let ch = expr[i];
        if ch.is_numeric() {
            num_q.push(expr[i].to_digit(10).unwrap());
            i += 1
        } else if ch == '*' {
            let a = num_q.pop().unwrap();
            let b = expr[i+1].to_digit(10).unwrap();
            num_q.push(a*b);
            i += 2;
        } else {
            i += 1;
        }
    }
    return num_q.iter().sum::<u32>();
}

fn left_to_right(expr: Vec<char>) -> u32 {
    let mut curr = expr[0].to_digit(10).unwrap();
    for i in (1..expr.len()).step_by(2) {
        let next = expr[i+1].to_digit(10).unwrap();
        curr = if expr[i] == '+' { curr+next } else { curr*next };
    }
    return curr;
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
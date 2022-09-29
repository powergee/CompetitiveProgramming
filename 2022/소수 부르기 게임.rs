fn main() {
    let scan = &mut Scanner::default();
    let (a, b) = (scan.usize(), scan.usize());
    let (c, d) = (scan.usize(), scan.usize());
    
    let is_prime = sieve_primes(b.max(d));

    let common = {
        if b < c || d < a {
            0
        } else {
            let mut points = [a, b, c, d];
            points.sort();
            (points[1]..=points[2])
                .filter(|n| is_prime[*n])
                .count()
        }
    };

    let yt = (a..=b)
        .filter(|n| is_prime[*n])
        .count() - common + (common%2);
    let yj = (c..=d)
        .filter(|n| is_prime[*n])
        .count() - common;

    if yt <= yj {
        println!("yj");
    } else {
        println!("yt");
    }
}

fn sieve_primes(last: usize) -> Vec<bool> {
    if last < 2 {
        return vec![false; last];
    }
    let mut is_prime = vec![true; last+1];
    is_prime[0] = false;
    is_prime[1] = false;
    
    for div in 2..=last {
        if is_prime[div] {
            for i in (div*div..=last).step_by(div) {
                is_prime[i] = false;
            }
        }
    }
    is_prime
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
    ($scan_type:ident, $single_scan_ident:ident, $multi_scan_ident:ident) => {
        impl Scanner {
            #[allow(unused)]
            fn $single_scan_ident(&mut self) -> $scan_type {
                self.next()
            }
            #[allow(unused)]
            fn $multi_scan_ident(&mut self, n: usize) -> Vec<$scan_type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    };
}
scanner_shortcut!(i32, i32, i32s);
scanner_shortcut!(i64, i64, i64s);
scanner_shortcut!(isize, isize, isizes);
scanner_shortcut!(u32, u32, u32s);
scanner_shortcut!(u64, u64, u64s);
scanner_shortcut!(usize, usize, usizes);
scanner_shortcut!(f64, f64, f64s);
scanner_shortcut!(String, string, strings);
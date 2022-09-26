fn main() {
    let scan = &mut Scanner::default();
    let (d, n, b) = (scan.f64(), scan.usize(), scan.usize());
    let obstacles = (0..n).map(|_| (scan.f64(), scan.f64())).collect::<Vec<_>>();
    
    let mut answer = f64::MAX;
    for bounce in 0..=b {
        let seg_len = d/(bounce as f64+1.0);
        let mut max_vx = f64::MAX;
        for seg_idx in 0..=bounce {
            let x_start = seg_idx as f64*seg_len;
            let x_end = x_start + seg_len;
            for obs in obstacles.iter().filter(|(x, _)| x_start <= *x && *x <= x_end) {
                let p = obs.0-x_start;
                let h = obs.1;
                max_vx = max_vx.min(
                    ((-p*p + seg_len*p)/(2.0*h)).sqrt()
                );
            }
        }
        if seg_len.sqrt()/2.0f64.sqrt() < max_vx {
            answer = answer.min(seg_len.sqrt());
        } else {
            answer = answer.min((max_vx.powf(2.0) + seg_len.powf(2.0)/(4.0*max_vx.powf(2.0))).sqrt());
        }
    }

    println!("{:.8}", answer);
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
scanner_shortcut!(f64);
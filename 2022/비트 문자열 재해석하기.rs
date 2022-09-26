fn main() {
    let scan = &mut Scanner::default();
    let (n, m) = (scan.usize(), scan.usize());
    let origin = (0..n).map(|_| scan.i32()).collect::<Vec<_>>();
    let span = (0..m).map(|_| scan.i32()).collect::<Vec<_>>();

    let answer = std::cmp::min(
        get_min_cost(&origin, build_target(0, &span)),
        get_min_cost(&origin, build_target(1, &span))
    );
    println!("{}", answer);
}

fn build_target(start: i32, span: &Vec<i32>) -> Vec<i32> {
    let mut curr = start;
    let mut result = vec![];
    for len in span {
        for _ in 0..*len {
            result.push(curr);
        }
        curr = curr ^ 1;
    }
    return result;
}

fn get_min_cost(origin: &Vec<i32>, target: Vec<i32>) -> usize {
    if origin.iter().sum::<i32>() != target.iter().sum::<i32>() {
        return usize::MAX;
    }
    let mut curr = origin.clone();
    let mut cost = 0;
    for i in 0..origin.len() {
        if curr[i] != target[i] {
            let to_bring = curr.iter().skip(i).position(|&v| v == target[i]).unwrap()+i;
            cost += to_bring - i;
            for j in (i+1..=to_bring).rev() {
                let t = curr[j];
                curr[j] = curr[j-1];
                curr[j-1] = t;
            }
        }
    }
    return cost;
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
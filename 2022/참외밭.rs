use std::cmp::{max, min};

fn main() {
    let scan = &mut Scanner::default();
    
    let mut xs = vec![];
    let mut ys = vec![];
    let mut x = 0;
    let mut y = 0;
    let n: i32 = scan.next();
    for _ in 0..6 {
        let dir: usize = scan.next();
        let dist: i32 = scan.next();
        match dir {
            1 => { x += dist }
            2 => { x -= dist }
            3 => { y -= dist }
            4 => { y += dist }
            _ => panic!("invalid dir")
        }
        xs.push(x);
        ys.push(y);
    }

    let mut xs_unique = xs.clone();
    let mut ys_unique = ys.clone();
    xs_unique.sort_unstable();
    xs_unique.dedup();
    ys_unique.sort_unstable();
    ys_unique.dedup();

    let mut area = (xs_unique[2]-xs_unique[0]) * (ys_unique[2]-ys_unique[0]);
    for i in 0..6 {
        if xs[i] == xs_unique[1] && ys[i] == ys_unique[1] {
            let prev = if i == 0 { 5 } else { i-1 };
            let next = if i == 5 { 0 } else { i+1 };
            let rx = max(xs[i], max(xs[prev], xs[next]));
            let lx = min(xs[i], min(xs[prev], xs[next]));
            let ty = max(ys[i], max(ys[prev], ys[next]));
            let by = min(ys[i], min(ys[prev], ys[next]));
            area -= (rx-lx) * (ty-by);
            break;
        }
    }

    println!("{}", n*area);
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
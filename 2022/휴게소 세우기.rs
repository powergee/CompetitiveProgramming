fn main() {
    let io = &mut Scanner::default();
    
    let n: usize = io.next::<usize>() + 2;
    let m: usize = io.next();
    let l: usize = io.next();

    let mut points: Vec<usize> = (0..(n-2)).map(|_| io.next()).collect();
    points.push(0);
    points.push(l);
    points.sort_unstable();
    
    let is_valid = |max_dist: usize| {
        let mut need = 0;
        for i in 0..n-1 {
            let dist = points[i+1] - points[i];
            need += dist/max_dist;
            if dist/max_dist > 0 && dist%max_dist == 0 {
                need -= 1;
            }
        }
        return need <= m;
    };

    let mut left = 1;
    let mut right = l;
    while left < right {
        let mid = (left+right) / 2;
        if is_valid(mid) {
            right = mid;
        } else {
            left = mid+1;
        }
    }

    println!("{left}");
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
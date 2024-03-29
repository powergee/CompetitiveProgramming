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

fn main() {
    let scan = &mut Scanner::default();
    let n: i32 = scan.next();
    let m: i32 = scan.next();

    let mut arr: Vec<i32> = (0..n).map(|_| scan.next()).collect();
    arr.sort();
    println!("{}", arr[(n-m) as usize]);
}
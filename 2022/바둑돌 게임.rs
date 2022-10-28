fn main() {
    let mut line = String::new();
    let stdin = std::io::stdin();
    stdin.read_line(&mut line).unwrap();

    let n = line.trim().parse::<usize>().unwrap();
    let mut round = 1;
    loop {
        let removed = round * (round+1) / 2;
        if removed >= n {
            println!("{}", removed-n);
            break;
        } else if n-removed < round+1 {
            println!("0");
            break;
        }
        round += 2;
    }
}
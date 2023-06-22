use std::io::{stdin, stdout, BufRead, BufWriter, Write};

fn main() {
    let mut stdin = stdin().lock();
    let mut writer = BufWriter::new(stdout().lock());
    loop {
        let mut buf = String::default();
        stdin.read_line(&mut buf).unwrap();
        let line = buf.trim();
        if line == "-1" {
            break;
        }
        let n = line.parse::<usize>().unwrap();

        let mut divs = vec![];
        for p in 1..n {
            if n % p == 0 {
                divs.push(p);
            }
        }

        if divs.iter().fold(0, |acc, &p| acc + p) == n {
            writeln!(
                writer,
                "{} = {}",
                n,
                divs.into_iter()
                    .map(|p| p.to_string())
                    .collect::<Vec<_>>()
                    .join(" + ")
            )
            .unwrap();
        } else {
            writeln!(writer, "{} is NOT perfect.", n).unwrap();
        }
    }
}

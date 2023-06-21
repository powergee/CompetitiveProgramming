use std::{
    io::{stdin, stdout, BufRead, BufWriter, Write},
    iter::repeat,
};

fn main() {
    let mut buf = String::default();
    stdin().lock().read_line(&mut buf).unwrap();
    let n = buf.trim().parse::<usize>().unwrap();

    let mut writer = BufWriter::new(stdout().lock());
    for i in 0..n {
        writeln!(
            writer,
            "{}",
            repeat(' ')
                .take(n - i - 1)
                .chain(repeat('*').take(2 * i + 1))
                .collect::<String>()
        )
        .unwrap();
    }
    for i in (0..n - 1).rev() {
        writeln!(
            writer,
            "{}",
            repeat(' ')
                .take(n - i - 1)
                .chain(repeat('*').take(2 * i + 1))
                .collect::<String>()
        )
        .unwrap();
    }
}

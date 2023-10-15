use std::io::{stdin, BufRead};

fn main() {
    let mut buf = String::new();
    stdin().lock().read_line(&mut buf).unwrap();
    let buf = buf.trim();
    println!(
        "{}",
        match parse(buf.as_bytes()) {
            Some((val, len)) =>
                if len == buf.as_bytes().len() {
                    val
                } else {
                    -1
                },
            None => -1,
        }
    );
}

fn parse(buf: &[u8]) -> Option<(i32, usize)> {
    match buf.first()? {
        b'x' => Some((0, 1)),
        b'g' => parse(&buf[1..]).map(|(val, len)| (val + 1, len + 1)),
        b'f' => {
            let (v1, l1) = parse(&buf[1..])?;
            let (v2, l2) = parse(&buf[1 + l1..])?;
            Some((v1.min(v2), 1 + l1 + l2))
        }
        _ => unreachable!(),
    }
}

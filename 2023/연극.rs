use std::io::{stdin, stdout, BufRead, BufWriter, Write};

fn main() {
    let buf = &mut String::new();
    stdin().lock().read_line(buf).unwrap();
    let n = buf.trim().parse::<usize>().unwrap();

    let mut curr = vec![1, 1];
    for i in 2..=n {
        let mut next = Vec::with_capacity(curr.len() * 2);
        next.push(i);
        next.append(&mut curr.clone());
        let alive = *next.last().unwrap();
        *next.last_mut().unwrap() = i;

        let origin = curr[0];
        next.extend(curr.into_iter().skip(1).map(|v| {
            if v == alive {
                origin
            } else if v == origin {
                alive
            } else {
                v
            }
        }));
        curr = next;
    }

    let mut writer = BufWriter::new(stdout().lock());
    writeln!(writer, "{}", curr.len() - 1).unwrap();
    for ans in curr {
        writeln!(writer, "{}", ans).unwrap();
    }
}

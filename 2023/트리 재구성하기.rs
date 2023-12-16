use std::io::{stdout, BufWriter, Write};

fn main() {
    let mut input = In::stdin();
    let n = input.read::<usize>();
    let knead = scan_edges(&mut input, n);
    let roll_out = scan_edges(&mut input, n);

    let mut writer = BufWriter::new(stdout().lock());
    writeln!(writer, "{}", knead.len() + roll_out.len()).unwrap();

    let knead = knead.into_iter().map(|(p, c)| (c, p, 1));
    let roll_out = roll_out.into_iter().map(|(p, c)| (c, 1, p)).rev();
    let answer = knead.chain(roll_out);

    for (a, b, c) in answer {
        writeln!(writer, "{a} {b} {c}").unwrap();
    }
}

fn scan_edges(input: &mut In, n: usize) -> Vec<(usize, usize)> {
    let mut graph = vec![vec![]; n + 1];
    for _ in 0..n - 1 {
        let (u, v): (usize, usize) = (input.read(), input.read());
        graph[u].push(v);
        graph[v].push(u);
    }

    let mut i = 0;
    let mut result = graph[1]
        .iter()
        .flat_map(|&u| {
            graph[u]
                .iter()
                .filter_map(move |&v| if 1 != v { Some((u, v)) } else { None })
        })
        .collect::<Vec<_>>();
    while i < result.len() {
        let (p, u) = result[i];
        for &v in &graph[u] {
            if v != p {
                result.push((u, v));
            }
        }
        i += 1;
    }
    result
}

struct In(std::str::SplitAsciiWhitespace<'static>, String);

impl In {
    fn stdin() -> Self {
        let buf = std::io::read_to_string(std::io::stdin().lock()).unwrap();
        let iter = unsafe { std::mem::transmute(buf.trim().split_ascii_whitespace()) };
        Self(iter, buf)
    }

    fn read<T: std::str::FromStr + std::fmt::Debug>(&mut self) -> T {
        self.0.next().and_then(|s| s.parse::<T>().ok()).unwrap()
    }
}

#![allow(unused)]
use std::{
    collections::BTreeSet,
    io::{BufRead, BufWriter, Write},
};

fn main() {
    let stdin = std::io::stdin();
    let stdout = std::io::stdout();
    let io = &mut IO::new(stdin.lock(), stdout.lock());

    let tt = io.usize();
    for _ in 0..tt {
        let (n, m) = (io.usize(), io.usize());
        let mut cases = (0..m)
            .map(|_| {
                (
                    io.string().chars().map(|ch| ch == '1').collect::<Vec<_>>(),
                    io.usize() == 1,
                )
            })
            .collect::<Vec<_>>();

        let mut ok = true;
        while !cases.is_empty() {
            let mut reduced = false;
            for (i, finding_input) in (0..n).flat_map(|i| std::iter::repeat(i).zip([false, true])) {
                let mut selected_output = None;
                let mut selected = BTreeSet::new();
                let mut valid = true;
                for (j, (inputs, output)) in cases.iter().enumerate() {
                    if inputs[i] == finding_input {
                        if let Some(selected_output) = selected_output {
                            if selected_output == output {
                                selected.insert(j);
                            } else {
                                valid = false;
                                break;
                            }
                        } else {
                            selected_output = Some(output);
                            selected.insert(j);
                        }
                    }
                }

                if valid && selected_output.is_some() {
                    cases = cases
                        .iter()
                        .enumerate()
                        .filter(|(i, _)| !selected.contains(i))
                        .map(|(_, x)| x.clone())
                        .collect();
                    reduced = true;
                    break;
                }
            }
            if !reduced {
                ok = false;
                break;
            }
        }

        writeln!(io.writer, "{}", (if ok { "OK" } else { "LIE" })).unwrap();
    }
}

// Modified EbTech's Scanner
pub struct IO<R, W: Write> {
    reader: R,
    writer: BufWriter<W>,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
}

impl<R: BufRead, W: Write> IO<R, W> {
    pub fn new(reader: R, writer: W) -> Self {
        Self {
            reader,
            writer: BufWriter::new(writer),
            buf_str: String::new(),
            buf_iter: "".split_whitespace(),
        }
    }

    #[inline]
    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader
                .read_line(&mut self.buf_str)
                .expect("Failed read");
            self.buf_iter = unsafe { std::mem::transmute(self.buf_str.split_whitespace()) };
        }
    }
}

macro_rules! io_shortcut {
    ($scan_type:ident, $single_ident:ident, $multi_ident:ident) => {
        impl<R: BufRead, W: Write> IO<R, W> {
            #[inline]
            #[allow(unused)]
            fn $single_ident(&mut self) -> $scan_type {
                self.next()
            }
            #[inline]
            #[allow(unused)]
            fn $multi_ident(&mut self, n: usize) -> Vec<$scan_type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    };
}
io_shortcut!(i64, i64, i64s);
io_shortcut!(u64, u64, u64s);
io_shortcut!(usize, usize, usizes);
io_shortcut!(f64, f64, f64s);
io_shortcut!(String, string, strings);

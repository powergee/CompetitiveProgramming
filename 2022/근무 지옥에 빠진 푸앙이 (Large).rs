use std::{io::{BufRead, BufWriter, Write}, collections::HashMap};

const AMOUNT: &[usize] = &[4, 6, 4, 10];

fn main() {
    let stdin = std::io::stdin();
    let stdout = std::io::stdout();
    let io = &mut IO::new(stdin.lock(), stdout.lock());

    let n = io.usize();
    let mut workers = HashMap::new();
    
    for _ in 0..n {
        for period in 0..4 {
            for _ in 0..7 {
                let name = io.string();
                if name != "-" {
                    *workers.entry(name).or_insert(0) += AMOUNT[period];
                }
            }
        }
    }

    let hours = workers.iter().map(|(_, hour)| hour).copied().collect::<Vec<_>>();
    if hours.is_empty() || hours.iter().max().unwrap() - hours.iter().min().unwrap() <= 12 {
        writeln!(io.writer, "Yes").unwrap();
    } else {
        writeln!(io.writer, "No").unwrap();
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
            buf_iter: "".split_whitespace()
        }
    }

    pub fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return token.parse().ok().expect("Failed parse");
            }
            self.buf_str.clear();
            self.reader.read_line(&mut self.buf_str).expect("Failed read");
            self.buf_iter = unsafe { std::mem::transmute(self.buf_str.split_whitespace()) };
        }
    }
}

macro_rules! io_shortcut {
    ($scan_type:ident, $single_ident:ident, $multi_ident:ident) => {
        impl<R: BufRead, W: Write> IO<R, W> {
            #[allow(unused)]
            fn $single_ident(&mut self) -> $scan_type {
                self.next()
            }
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
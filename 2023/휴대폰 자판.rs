use std::cmp::Ordering;
use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    loop {
        let n: usize = match io.next() {
            Some(n) => n,
            None => break,
        };
        let mut words = (0..n)
            .map(|_| format!("{:0<80}", io.next::<String>().unwrap()))
            .collect::<Vec<_>>();
        words.push(unsafe { String::from_utf8_unchecked(vec![b'z' + 1; 80]) });
        words.sort();

        let mut total = 0usize;
        for word in words.iter().take(n).map(|w| w.as_bytes()) {
            let mut typed = 1;
            let mut range = equal_range(&words, 0, n, 0, word[0]);
            for i in 1..word.len() {
                if word[i] == b'0' {
                    break;
                }
                let curr_range = equal_range(&words, range.0, range.1, i, word[i]);
                if range != curr_range {
                    typed += 1;
                }
                range = curr_range;
            }
            total += typed;
        }
        writeln!(
            io.writer,
            "{:.2}",
            ((total as f64) / (n as f64) * 100.0).round() / 100.0
        )
        .unwrap();
    }
}

fn equal_range(
    words: &Vec<String>,
    min_left: usize,
    max_right: usize,
    cidx: usize,
    pivot: u8,
) -> (usize, usize) {
    let left = words[min_left..max_right]
        .binary_search_by(|x| match x.as_bytes()[cidx].cmp(&pivot) {
            Ordering::Equal => Ordering::Greater,
            ord => ord,
        })
        .unwrap_err()
        + min_left;
    let right = words[min_left..max_right]
        .binary_search_by(|x| match x.as_bytes()[cidx].cmp(&(pivot + 1)) {
            Ordering::Equal => Ordering::Greater,
            ord => ord,
        })
        .unwrap_err()
        + min_left;
    (left, right)
}

// Modified EbTech's Scanner
pub struct IO<R, W: Write> {
    reader: R,
    writer: BufWriter<W>,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
}

impl IO<StdinLock<'static>, StdoutLock<'static>> {
    pub fn stdio() -> Self {
        Self::new(stdin().lock(), stdout().lock())
    }
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
    pub fn next<T: std::str::FromStr>(&mut self) -> Option<T> {
        loop {
            if let Some(token) = self.buf_iter.next() {
                return Some(token.parse().ok().expect("Failed parse"));
            }
            self.buf_str.clear();
            let read = self
                .reader
                .read_line(&mut self.buf_str)
                .expect("Failed read");
            if read == 0 {
                return None;
            }
            self.buf_iter = unsafe { std::mem::transmute(self.buf_str.split_whitespace()) };
        }
    }
}

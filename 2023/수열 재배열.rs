use std::{
    collections::BTreeSet,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
};

fn main() {
    let mut io = IO::stdio();

    let (n, k) = (io.usize(), io.usize());
    let arr = io.usizes(n);
    let mut left_asc = vec![0; n];
    let mut right_asc = vec![0; n];

    left_asc[0] = 1;
    for i in 1..n {
        if arr[i - 1] < arr[i] {
            left_asc[i] = left_asc[i - 1] + 1;
        } else {
            left_asc[i] = 1;
        }
    }

    right_asc[n - 1] = 1;
    for i in (0..n - 1).rev() {
        if arr[i] < arr[i + 1] {
            right_asc[i] = right_asc[i + 1] + 1;
        } else {
            right_asc[i] = 1;
        }
    }

    let mut window = BTreeSet::new();
    for i in 0..k - 1 {
        window.insert(arr[i]);
    }

    let mut answer = k.max(*left_asc.iter().max().unwrap());
    for i in k - 1..n {
        window.insert(arr[i]);

        if k <= i {
            answer = answer.max(left_asc[i - k] + window.range(arr[i - k]..).count());
        }
        if i + 1 < arr.len() {
            answer = answer.max(right_asc[i + 1] + window.range(0..arr[i + 1]).count());
        }
        if k <= i
            && i + 1 < arr.len()
            && arr[i - k] < *window.iter().next().unwrap()
            && *window.iter().next_back().unwrap() < arr[i + 1]
        {
            answer = answer.max(k + left_asc[i - k] + right_asc[i + 1]);
        }

        window.remove(&arr[i + 1 - k]);
    }

    writeln!(io.writer, "{answer}").unwrap();
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
io_shortcut!(usize, usize, usizes);

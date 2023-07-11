use std::{
    cmp::Reverse,
    io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write},
    iter::once,
};

fn main() {
    let mut io = IO::stdio();
    let n = io.usize();
    let costs = (0..n).map(|v| (io.usize(), Reverse(v))).collect::<Vec<_>>();
    let mut m = io.usize();

    if costs
        .iter()
        .filter_map(|(cost, v)| if *cost <= m { Some(v.0) } else { None })
        .eq(once(0))
    {
        writeln!(io.writer, "0").unwrap();
        return;
    }

    let mut answer = vec![*costs.iter().skip(1).min().unwrap()];
    m -= answer[0].0;
    let cheapest = *costs.iter().min().unwrap();
    for _ in 0..m / cheapest.0 {
        answer.push(cheapest);
    }
    m = m - m / cheapest.0 * cheapest.0;

    for i in 0..answer.len() {
        m += answer[i].0;
        for v in (0..n).rev() {
            if costs[v].0 <= m {
                m -= costs[v].0;
                answer[i] = costs[v];
                break;
            }
        }
    }
    writeln!(
        io.writer,
        "{}",
        answer
            .into_iter()
            .map(|(_, Reverse(v))| (b'0' + v as u8) as char)
            .collect::<String>()
    )
    .unwrap();
}

/// Modified EbTech's Scanner
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

macro_rules! io_shortcut {(
    $(($type:ident, $types:ident))*
) => (
    $(
        impl<R: BufRead, W: Write> IO<R, W> {
            #[inline]
            #[allow(unused)]
            fn $type(&mut self) -> $type {
                self.next()
            }
            #[inline]
            #[allow(unused)]
            fn $types(&mut self, n: usize) -> Vec<$type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    )*
)}

io_shortcut! {
    (u8, u8s) (u16, u16s) (u32, u32s) (u64, u64s) (u128, u128s)
    (i8, i8s) (i16, i16s) (i32, i32s) (i64, i64s) (i128, i128s)
    (usize, usizes) (isize, isizes) (f64, f64s)
}

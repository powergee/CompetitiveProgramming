use std::io::{stdin, stdout, BufRead, BufWriter, StdinLock, StdoutLock, Write};

fn main() {
    let mut io = IO::stdio();
    let (n, q) = (io.usize(), io.usize());
    let mut capacity = io.usizes(n);
    capacity.push(usize::MAX);
    let mut drunken = vec![0; n + 1];
    let mut state = State::new(n + 1);

    for _ in 0..q {
        let (t, i) = (io.usize(), io.usize());
        match t {
            1 => {
                let mut x = io.usize();
                while x > 0 {
                    let next = state.find_next(i - 1);
                    if drunken[next] + x >= capacity[next] {
                        x = drunken[next] + x - capacity[next];
                        drunken[next] = capacity[next];
                        state.advance_next(i - 1);
                    } else {
                        drunken[next] = drunken[next] + x;
                        x = 0;
                    }
                }
            }
            2 => writeln!(io.writer, "{}", drunken[i - 1]).unwrap(),
            _ => unreachable!(),
        }
    }
}

struct State {
    next: Vec<usize>,
}

impl State {
    fn new(size: usize) -> State {
        let next = (0..size).collect();
        State { next }
    }

    fn find_next(&mut self, x: usize) -> usize {
        let n = self.next.get(x).expect("State: x is out of range");
        if *n == x {
            x
        } else {
            let new_next = self.find_next(n.clone());
            self.next[x] = new_next;
            new_next
        }
    }

    fn advance_next(&mut self, x: usize) {
        let x_next = self.find_next(x);
        self.next[x_next] = x_next + 1;
    }
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

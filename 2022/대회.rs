use std::{io::BufRead, collections::BTreeSet};
use std::ops::Bound::{Included, Unbounded};

fn main() {
    let stdin = std::io::stdin();
    let scan = &mut Scanner::new(stdin.lock());
    let (n, k) = (scan.usize(), scan.usize());
    let mut contests = (0..n).map(|_| (scan.usize(), scan.usize())).collect::<Vec<_>>();
    contests.sort_by_key(|(s, e)| (*e, *s));

    let mut missed = 0;
    let mut active = 1;
    let mut oppo = (0..k-1).map(|i| (1, i)).collect::<BTreeSet<_>>();
    for (s, e) in contests {
        if s < active {
            continue;
        }
        let mut usable = oppo.range((Unbounded, Included((s, k))));
        if let Some((free, idx)) = usable.next_back() {
            let new_bucket = (e+1, *idx);
            oppo.remove(&(*free, *idx));
            oppo.insert(new_bucket);
        } else {
            missed += 1;
            active = e+1;
        }
    }

    println!("{missed}");
}

// From EbTech
pub struct Scanner<B> {
    reader: B,
    buf_str: String,
    buf_iter: std::str::SplitWhitespace<'static>,
}

impl<B: BufRead> Scanner<B> {
    pub fn new(reader: B) -> Self {
        Self {
            reader,
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


macro_rules! scanner_shortcut {
    ($scan_type:ident, $single_scan_ident:ident, $multi_scan_ident:ident) => {
        impl<B: BufRead> Scanner<B> {
            #[allow(unused)]
            fn $single_scan_ident(&mut self) -> $scan_type {
                self.next()
            }
            #[allow(unused)]
            fn $multi_scan_ident(&mut self, n: usize) -> Vec<$scan_type> {
                (0..n).map(|_| self.next()).collect()
            }
        }
    };
}
scanner_shortcut!(usize, usize, usizes);
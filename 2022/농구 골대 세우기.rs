use std::collections::BTreeMap;

fn main() {
    let scan = &mut Scanner::default();
    
    let n = scan.usize();
    let mut pt_by_x: BTreeMap<i32, Vec<(i32, i32)>> = BTreeMap::new();
    let mut pt_by_y: BTreeMap<i32, Vec<(i32, i32)>> = BTreeMap::new();
    let mut total_pop = 0i64;
    for _ in 0..n {
        let (x, y, p) = (scan.i32(), scan.i32(), scan.i32());
        total_pop += p as i64;
        pt_by_x.entry(x)
            .and_modify(|bucket| bucket.push((y, p)))
            .or_insert(vec![(y, p)]);
        pt_by_y.entry(y)
            .and_modify(|bucket| bucket.push((x, p)))
            .or_insert(vec![(x, p)]);
    }

    let x_min = pt_by_x.iter().next().unwrap().0.clone();
    let x_max = pt_by_x.iter().next_back().unwrap().0.clone();
    let y_min = pt_by_y.iter().next().unwrap().0.clone();
    let y_max = pt_by_y.iter().next_back().unwrap().0.clone();

    let sweep_coord = |pt: BTreeMap<i32, Vec<(i32, i32)>>, min: i32, max: i32| {
        let mut answer = (i64::MAX, 0);
        let mut per_step = -total_pop.clone();
        let mut window = 0;
        // init window
        for (x, bucket) in &pt {
            for (_, p) in bucket {
                window += (x.clone()-min) as i64 * p.clone() as i64;
            }
        }
        for x in min..=max {
            answer = answer.min((window, x));
            if let Some(bucket) = pt.get(&x) {
                for (_, p) in bucket {
                    per_step += 2*(p.clone() as i64);
                }
            }
            window += per_step;
        }
        answer
    };
    
    let answer_x = sweep_coord(pt_by_x, x_min, x_max);
    let answer_y = sweep_coord(pt_by_y, y_min, y_max);
    println!("{} {}", answer_x.1, answer_y.1);
}

#[derive(Default)]
struct Scanner {
    buffer: Vec<String>
}

impl Scanner {
    fn next<T: std::str::FromStr>(&mut self) -> T {
        loop {
            if let Some(token) = self.buffer.pop() {
                return token.parse().ok().expect("Failed parse");
            }
            let mut input = String::new();
            std::io::stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

macro_rules! scanner_shortcut {
    ($scan_type:ident, $single_scan_ident:ident, $multi_scan_ident:ident) => {
        impl Scanner {
            #[allow(unused)]
            fn $single_scan_ident(&mut self) -> $scan_type {
                self.next()
            }
            #[allow(unused)]
            fn $multi_scan_ident(&mut self, n: usize, padding: usize) -> Vec<$scan_type> {
                std::iter::repeat(Default::default())
                    .take(padding)
                    .chain((0..n).map(|_| self.next()))
                    .collect()
            }
        }
    };
}
scanner_shortcut!(i32, i32, i32s);
scanner_shortcut!(i64, i64, i64s);
scanner_shortcut!(isize, isize, isizes);
scanner_shortcut!(u32, u32, u32s);
scanner_shortcut!(u64, u64, u64s);
scanner_shortcut!(usize, usize, usizes);
scanner_shortcut!(f64, f64, f64s);
scanner_shortcut!(String, string, strings);
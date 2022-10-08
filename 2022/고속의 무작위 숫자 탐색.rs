use std::collections::VecDeque;

fn main() {
    let scan = &mut Scanner::default();
    let map = (0..5).map(|_| scan.i32s(5)).collect::<Vec<_>>();
    let (r, c) = (scan.usize(), scan.usize());
    
    let mut dist = vec![vec![vec![i32::MAX; 1<<6]; 5]; 5];
    let mut q = VecDeque::new();
    dist[r][c][0] = 0;
    q.push_back((r, c, 0));

    let dir = [
        (0, 1), (0, -1), (1, 0), (-1, 0)
    ];
    let get_point = |r, c, dr, dc, step| {
        let nr = r as i32 + dr*step;
        let nc = c as i32 + dc*step;
        if 0 <= nr && nr < 5 && 0 <= nc && nc < 5 && map[nr as usize][nc as usize] != -1 {
            Some((nr as usize, nc as usize))
        } else {
            None
        }
    };

    while let Some((r, c, visited)) = q.pop_front() {
        for (dr, dc) in dir {
            if let Some((nr, nc)) = get_point(r, c, dr, dc, 1) {
                let tile = map[nr][nc];
                let next_visited = if 1 <= tile && tile <= 6 {
                    visited | (1<<(tile-1))
                } else {
                    visited
                };
                if dist[nr][nc][next_visited] == i32::MAX {
                    dist[nr][nc][next_visited] = 1 + dist[r][c][visited];
                    q.push_back((nr, nc, next_visited));
                }

                let mut farthest = 1;
                for step in 1.. {
                    if let Some((nr, nc)) = get_point(r, c, dr, dc, step) {
                        farthest = step;
                        if map[nr][nc] == 7 {
                            break;
                        }
                    } else {
                        break;
                    }
                }

                let (nr, nc) = get_point(r, c, dr, dc, farthest).unwrap();
                let tile = map[nr][nc];
                let next_visited = if 1 <= tile && tile <= 6 {
                    visited | (1<<(tile-1))
                } else {
                    visited
                };
                if dist[nr][nc][next_visited] == i32::MAX {
                    dist[nr][nc][next_visited] = 1 + dist[r][c][visited];
                    q.push_back((nr, nc, next_visited));
                }
            }
        }
    }

    let mut answer = i32::MAX;
    for i in 0..5 {
        for j in 0..5 {
            answer = answer.min(dist[i][j][(1<<6)-1]);
        }
    }
    let answer = if answer == i32::MAX { -1 } else { answer };
    println!("{answer}");
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
            fn $multi_scan_ident(&mut self, n: usize) -> Vec<$scan_type> {
                (0..n).map(|_| self.next()).collect()
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
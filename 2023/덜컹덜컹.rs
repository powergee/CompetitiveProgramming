use std::io::{stdin, BufRead, StdinLock};

fn main() {
    let stdin = &mut stdin().lock();
    let mut n = read_usize(stdin);
    while n != 0 {
        let legs = (0..n).map(|_| read_usize(stdin)).collect::<Vec<_>>();
        let unit_deg = (2.0 * std::f64::consts::PI) / n as f64;

        let mut answer = usize::MAX;

        let evaluate = |hull: &[usize]| {
            let desired = hull.iter().fold(usize::MAX, |min, i| min.min(legs[*i]));
            legs.iter().fold(0, |total, length| {
                total + length.checked_sub(desired).unwrap_or(0)
            })
        };

        for i in 0..n {
            for j in i + 1..n {
                for k in j + 1..n {
                    if n % 2 == 0
                        && (i == (j + (n / 2)) % n
                            || j == (k + (n / 2)) % n
                            || k == (i + (n / 2)) % n)
                    {
                        continue;
                    }
                    let pi = point(unit_deg * i as f64);
                    let pj = point(unit_deg * j as f64);
                    let pk = point(unit_deg * k as f64);
                    if is_interior(&(0.0, 0.0), &[pi, pj, pk]) {
                        answer = answer.min(evaluate(&[i, j, k]));
                    }
                }
            }
        }
        if n % 4 == 0 {
            for i in 0..n {
                let j = (i + n / 4) % n;
                let k = (i + 2 * n / 4) % n;
                let l = (i + 3 * n / 4) % n;
                let pi = point(unit_deg * i as f64);
                let pj = point(unit_deg * j as f64);
                let pk = point(unit_deg * k as f64);
                let pl = point(unit_deg * l as f64);
                if is_interior(&(0.0, 0.0), &[pi, pj, pk, pl]) {
                    answer = answer.min(evaluate(&[i, j, k, l]));
                }
            }
        }

        println!("{answer}\n");
        n = read_usize(stdin);
    }
}

fn point(deg: f64) -> (f64, f64) {
    (f64::cos(deg), f64::sin(deg))
}

fn is_interior(p: &(f64, f64), hull: &[(f64, f64)]) -> bool {
    for i in 0..hull.len() {
        let j = (i + 1) % hull.len();
        if ccw(&hull[i], &hull[j], p) <= 0.0 {
            return false;
        }
    }
    return true;
}

fn ccw(p1: &(f64, f64), p2: &(f64, f64), p3: &(f64, f64)) -> f64 {
    p1.0 * p2.1 + p2.0 * p3.1 + p3.0 * p1.1 - p1.1 * p2.0 - p2.1 * p3.0 - p3.1 * p1.0
}

fn read_usize(stdin: &mut StdinLock<'_>) -> usize {
    let buf = &mut String::new();
    stdin.read_line(buf).unwrap();
    buf.trim().parse().unwrap()
}

use std::io::{BufWriter, stdout, Write};

const ROBUST_TEST_SET: &'static [(i64, &'static [i64])] = &[
    (2047, &[ 2 ]),
    (1373653, &[ 2, 3 ]),
    (9080191, &[ 31, 73 ]),
    (25326001, &[ 2, 3, 5 ]),
    (3215031751, &[ 2, 3, 5, 7 ]),
    (4759123141, &[ 2, 7, 61 ]),
    (1122004669633, &[ 2, 13, 23, 1662803 ]),
    (2152302898747, &[ 2, 3, 5, 7, 11 ]),
    (3474749660383, &[ 2, 3, 5, 7, 11, 13 ]),
    (341550071728321, &[ 2, 3, 5, 7, 11, 13, 17 ]),
    (3825123056546413051, &[ 2, 3, 5, 7, 11, 13, 17, 19, 23 ]),
    (0, &[ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 ]),
];

struct RNG {
    seed: i64
}

impl Default for RNG {
    fn default() -> RNG {
        RNG {
            seed: 1
        }
    }
}

impl RNG {
    fn next(&mut self) -> i64 {
        self.seed = (0xd9f5 * self.seed) % (1 << 32);
        self.seed
    }
}

fn gcd(a: i64, b: i64) -> i64 {
    if b == 0 { a } else { gcd(b, a%b) }
}

fn abs(a: i64) -> i64 {
    if a > 0 { a } else { -a }
}

fn get_mod_pow(val: i64, mut exp: i64, div: i64) -> i128 {
    let mut result: i128 = 1;
    let mut sub_power: i128 = i128::from(val % div);
    let div = i128::from(div);

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * sub_power) % div;
        }
        exp /= 2;
        sub_power = (sub_power * sub_power) % div;
    }
    result
}

fn do_miller_rabin_test(n: i64, a: i64) -> bool {
    let mut d = n-1;
    while d % 2 == 0 {
        d /= 2;
    }

    let n_128 = i128::from(n);
    let mut x = get_mod_pow(a, d, n);

    if x == 1 || x == n_128-1 {
        return true;
    }
    while d != n-1 {
        x = (x*x) % n_128;
        d *= 2;
        if x == n_128-1 {
            return true;
        }
    }
    false
}

fn is_prime(n: i64) -> bool {
    if n == 2 {
        return true;
    } else if n <= 1 || n % 2 == 0 {
        return false;
    }
    
    let found = ROBUST_TEST_SET.iter().position(|pair| n < pair.0);
    let index = if let None = found {
        ROBUST_TEST_SET.len()-1
    } else {
        found.unwrap()
    };

    let tests = &ROBUST_TEST_SET[index].1;
    !tests.into_iter().any(|a| !do_miller_rabin_test(n, *a))
}

fn factorize_rec(n: i64, result: &mut Vec<i64>) {
    if n <= 1 {
        return;
    } else if n % 2 == 0 {
        result.push(2);
        factorize_rec(n/2, result);
        return;
    } else if is_prime(n) {
        result.push(n);
        return;
    }

    let mut rng: RNG = RNG::default();
    let mut xs: i64 = 0;
    let mut xt: i64 = 0;
    let mut c: i64 = 0;
    let mut factor = n;
    let f = |x: i64, n: i64, c: i64| ((get_mod_pow(x, 2, n) as i64 + c) % n);

    loop {
        if factor == n {
            xs = rng.next() % (n-2) + 2;
            xt = xs;
            c = rng.next() % 20 + 1;
        }
        xs = f(xs, n, c);
        xt = f(xt, n, c);
        xt = f(xt, n, c);
        factor = gcd(abs(xs-xt), n);
        if factor != 1 && factor != n { break; }
    };

    factorize_rec(factor, result);
    factorize_rec(n/factor, result);
}

fn factorize(n: i64) -> Vec<i64> {
    let mut result: Vec<i64> = vec![];
    factorize_rec(n, &mut result);
    result.sort_unstable();
    result
}

fn main() {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("stdin error");
    let n: i64 = match line.trim().parse() {
        Ok(num) => num,
        Err(_) => 0
    };

    let out = &mut BufWriter::new(stdout());
    for f in factorize(n) {
        writeln!(out, "{}", f).ok();
    }
}
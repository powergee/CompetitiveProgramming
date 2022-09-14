use std::io::{BufWriter, stdout, Write};
use std::collections::{HashSet};

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

type Quadruple = [i64; 4];

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
        self.seed = (1103515245 * self.seed + 12345) % 0x7fffffff;
        self.seed
    }
}

fn get_bit_width(n: i64) -> i64 {
    let mut e: i64 = 1;
    while (1i64<<e) <= n { e += 1; }
    e-1
}

fn get_int_sqrt(n: i64) -> i64 {
    if n <= 1 { return n; }

    let mut x0 = n;
    let mut x1 = std::cmp::min(n/2, 1i64<<(get_bit_width(n)/2+1));

    while x1 < x0 {
        x0 = x1;
        x1 = (x0 + n/x0) / 2;
    }
    x0
}

fn is_perfect_square(n: i64) -> bool {
    let sqrt = get_int_sqrt(n);
    sqrt * sqrt == n
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

// Brahmagupta–Fibonacci identity
fn merge_as_two(a: &Quadruple, b: &Quadruple) -> Quadruple {
    [ abs(a[0]*b[0] - a[1]*b[1]), a[0]*b[1] + a[1]*b[0], 0, 0 ]
}

fn get_remainders(mut a: i64, mut b: i64, bound: i64) -> Vec<i64> {
    let bound_sqrt = get_int_sqrt(bound);
    let mut result: Vec<i64> = vec![];
    while b != 0 && result.len() < 2 {
        let r = a % b;
        if 0 < r && r <= bound_sqrt {
            result.push(r);
        }
        a = b;
        b = r;
    }
    result
}

// p is one or a prime number (1 or 2 or 4k+1)
fn find_sum_of_two(p: i64) -> Quadruple {
    if p == 1 {
        return [ 1, 0, 0, 0 ];
    } else if p == 2 {
        return [ 1, 1, 0, 0 ];
    }

    let mut rems;
    let mut rng = RNG::default();

    loop {
        let mut q = rng.next() % p;
        while get_mod_pow(q, (p-1)/2, p) as i64 != p-1 {
            q = rng.next() % p;
        }
        let x = get_mod_pow(q, (p-1)/4, p) as i64;
        rems = get_remainders(p, x, p);

        if rems.len() >= 2 {
            break [ rems[0], rems[1], 0, 0 ]
        }
    }
}

fn find_sum_of_three(n: i64) -> Quadruple {
    if let Some(exp) = check_rabin_exceptions(n) {
        exp
    } else if n % 4 == 0 {
        let sub = find_sum_of_three(n/4);
        [ sub[0]*2, sub[1]*2, sub[2]*2, sub[3]*2 ]
    } else if n % 8 == 7 {
        [ 0, 0, 0, 0 ] // Exception - Impossible
    } else if n % 8 == 3 {
        let mut rng = RNG::default();
        let mut x;
        let mut p;
        loop {
            x = rng.next() % (get_int_sqrt(n) + 1);
            p = (n - x*x) / 2;

            if (n-x*x) % 2 == 0 && (is_prime(p) || p == 1) { break; }
        }
        let two = find_sum_of_two(p);
        [ x, two[0]+two[1], abs(two[0]-two[1]), 0 ]
    } else if is_perfect_square(n) {
        [ get_int_sqrt(n), 0, 0, 0 ]
    } else {
        let mut rng = RNG::default();
        let mut x;
        let mut p;
        loop {
            x = rng.next() % (get_int_sqrt(n) + 1);
            p = n - x*x;
            if is_prime(p) { break; }
        }
        let two = find_sum_of_two(p);
        [ x, two[0], two[1], 0 ]
    }
}

fn check_rabin_exceptions(n: i64) -> Option<Quadruple> {
    match n {
        5 => Some([ 2, 1, 0, 0 ]),
        10 => Some([ 3, 1, 0, 0 ]),
        13 => Some([ 3, 2, 0, 0 ]),
        34 => Some([ 5, 3, 0, 0 ]),
        37 => Some([ 6, 1, 0, 0 ]),
        58 => Some([ 7, 3, 0, 0 ]),
        61 => Some([ 6, 5, 0, 0 ]),
        85 => Some([ 9, 2, 0, 0 ]),
        130 => Some([ 11, 3, 0, 0 ]),
        214 => Some([ 14, 3, 3, 0 ]),
        226 => Some([ 15, 1, 0, 0 ]),
        370 => Some([ 19, 3, 0, 0 ]),
        526 => Some([ 21, 9, 2, 0 ]),
        706 => Some([ 25, 9, 0, 0 ]),
        730 => Some([ 27, 1, 0, 0 ]),
        829 => Some([ 27, 10, 0, 0 ]),
        1414 => Some([ 33, 18, 1, 0 ]),
        1549 => Some([ 35, 18, 0, 0 ]),
        1906 => Some([ 41, 15, 0, 0 ]),
        2986 => Some([ 45, 31, 0, 0 ]),
        7549 => Some([ 85, 18, 0, 0 ]),
        9634 => Some([ 97, 15, 0, 0 ]),
        _ => None
    }
}

fn find_solution(n: i64) -> Quadruple {
    if n == 1 {
        return [ 1, 0, 0, 0 ];
    } else if n == 2 {
        return [ 1, 1, 0, 0 ];
    } else if n == 3 {
        return [ 1, 1, 1, 0 ];
    }

    // n이 4의 배수라면 이를 제거해줌.
    // 아래에서 n = 4^a mod 8 = 7 인지 체크하여 4개의 수가 필요한지를 체크하기 때문.
    if n % 4 == 0 {
        let sub = find_solution(n/4);
        return [ sub[0]*2, sub[1]*2, sub[2]*2, sub[3]*2 ];
    }

    // 완전 제곱수라면 1개로 표현. (필요충분)
    if is_perfect_square(n) {
        return [ get_int_sqrt(n), 0, 0, 0 ];
    }

    // n mod 8 = 7 이라면 무조건 4개의 수가 필요. (필요충분)
    // n = 4 + (n-4)로 분할하면 (n-4) mod 8 = 3 이므로 3개 내로 표현 가능할 테고,
    // 그럼 { 2, solution of (n-4) }가 해가 될 것.
    if n % 8 == 7 {
        let sub = find_sum_of_three(n-4);
        return [ 2, sub[0], sub[1], sub[2] ];
    }

    let primes = factorize(n);
    let mut even_acc: i64 = 1;
    let mut f_with_odd_exp = HashSet::new();
    for p in primes {
        if f_with_odd_exp.contains(&p) {
            even_acc *= p;
            f_with_odd_exp.remove(&p);
        } else {
            f_with_odd_exp.insert(p);
        }
    }

    // n mod 8 != 7 이라면 2개 or 3개로 만들 수 있음.
    // oddCount에 포함된 p에는 2 or 4k+1 꼴 or 4k+3 꼴의 소수가 있을 수 있는데
    // 2와 4k+1은 2개의 제곱수로 나타낼 수 있으나,
    // 4k+3는 3개의 제곱수 필요.
    if f_with_odd_exp.iter().any(|p| p % 4 == 3) {
        return find_sum_of_three(n);
    }

    let f_with_odd_exp: Vec<i64> = f_with_odd_exp.into_iter().collect();
    let mut result = find_sum_of_two(f_with_odd_exp[0]);
    for i in 1..(f_with_odd_exp.len()) {
        result = merge_as_two(&result, &find_sum_of_two(f_with_odd_exp[i]));
    }
    return [
        result[0]*even_acc,
        result[1]*even_acc,
        result[2]*even_acc,
        result[3]*even_acc
    ];
}

fn main() {
    let mut line = String::new();
    std::io::stdin().read_line(&mut line).expect("stdin error");
    let n: i64 = match line.trim().parse() {
        Ok(num) => num,
        Err(_) => 0
    };

    let result = find_solution(n);
    let mut comp = vec![];
    for i in 0..4 {
        if result[i] > 0 {
            comp.push(result[i]);
        }
    }

    let out = &mut BufWriter::new(stdout());
    writeln!(out, "{}", comp.len()).ok();
    for v in comp {
        write!(out, "{} ", v).ok();
    }
    writeln!(out, "").ok();
}
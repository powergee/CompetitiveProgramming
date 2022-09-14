use std::io::{stdin};

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
            stdin().read_line(&mut input).expect("Failed read");
            self.buffer = input.split_whitespace().rev().map(String::from).collect();
        }
    }
}

fn get_mod_pow(val: i128, mut exp: i128, div: i128) -> i128 {
    let mut result: i128 = 1;
    let mut sub_power: i128 = val % div;

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * sub_power) % div;
        }
        exp /= 2;
        sub_power = (sub_power * sub_power) % div;
    }
    result
}

fn do_miller_rabin_test(n: i128, a: i128) -> bool {
    let mut d = n-1;
    while d % 2 == 0 {
        d /= 2;
    }
    
    let mut x = get_mod_pow(a, d, n);
    if x == 1 || x == n-1 {
        return true;
    }
    while d != n-1 {
        x = (x*x) % n;
        d *= 2;
        if x == n-1 {
            return true;
        }
    }
    false
}

fn is_prime(n: i128, robust_test_sets: &Vec<(i128, Vec<i128>)>) -> bool {
    if n == 2 {
        return true;
    } else if n <= 1 || n % 2 == 0 {
        return false;
    }
    
    let found = robust_test_sets.iter().position(|pair| n < pair.0);
    let index = if let None = found {
        robust_test_sets.len()-1
    } else {
        found.unwrap()
    };

    let tests = &robust_test_sets[index].1;
    !tests.into_iter().any(|a| !do_miller_rabin_test(n, *a))
}

fn main() {
    let robust_test_sets: Vec<(i128, Vec<i128>)> = vec![
        (2047, vec![ 2 ]),
        (1373653, vec![ 2, 3 ]),
        (9080191, vec![ 31, 73 ]),
        (25326001, vec![ 2, 3, 5 ]),
        (3215031751, vec![ 2, 3, 5, 7 ]),
        (4759123141, vec![ 2, 7, 61 ]),
        (1122004669633, vec![ 2, 13, 23, 1662803 ]),
        (2152302898747, vec![ 2, 3, 5, 7, 11 ]),
        (3474749660383, vec![ 2, 3, 5, 7, 11, 13 ]),
        (341550071728321, vec![ 2, 3, 5, 7, 11, 13, 17 ]),
        (3825123056546413051, vec![ 2, 3, 5, 7, 11, 13, 17, 19, 23 ]),
        (0, vec![ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37 ]),
    ];

    let mut scan = Scanner::default();

    let t = scan.next::<usize>();
    let n_arr: Vec<i128> = (0..t).map(|_| scan.next()).collect();
    let mut answer = 0;
    for n in n_arr.iter() {
        answer += if is_prime(2*n + 1, &robust_test_sets) { 1 } else { 0 };
    }
    println!("{}", answer);
}
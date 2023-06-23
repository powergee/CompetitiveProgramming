const ROBUST_TEST_SETS: &'static [(u64, &'static [u64])] = &[
    (2047, &[2]),
    (1373653, &[2, 3]),
    (9080191, &[31, 73]),
    (25326001, &[2, 3, 5]),
    (3215031751, &[2, 3, 5, 7]),
    (4759123141, &[2, 7, 61]),
    (1122004669633, &[2, 13, 23, 1662803]),
    (2152302898747, &[2, 3, 5, 7, 11]),
    (3474749660383, &[2, 3, 5, 7, 11, 13]),
    (341550071728321, &[2, 3, 5, 7, 11, 13, 17]),
    (3825123056546413051, &[2, 3, 5, 7, 11, 13, 17, 19, 23]),
    (0, &[2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37]),
];

fn mod_pow(val: u64, mut exp: u64, div: u64) -> u128 {
    let mut result: u128 = 1;
    let mut sub_power = (val % div) as u128;

    while exp > 0 {
        if exp % 2 == 1 {
            result = (result * sub_power) % (div as u128);
        }
        exp /= 2;
        sub_power = (sub_power * sub_power) % (div as u128);
    }
    result
}

fn test_miller_rabin(n: u64, a: u64) -> bool {
    let mut d = n - 1;
    while d % 2 == 0 {
        d /= 2;
    }

    let mut x = mod_pow(a, d, n);
    if x == 1 || x == (n - 1) as u128 {
        return true;
    }
    while d != n - 1 {
        x = (x * x) % n as u128;
        d *= 2;
        if x == (n - 1) as u128 {
            return true;
        }
    }
    false
}

fn is_prime(n: u64) -> bool {
    if n == 2 {
        return true;
    } else if n <= 1 || n % 2 == 0 {
        return false;
    }

    let index = ROBUST_TEST_SETS
        .iter()
        .position(|pair| n < pair.0)
        .unwrap_or(ROBUST_TEST_SETS.len() - 1);

    let tests = &ROBUST_TEST_SETS[index].1;
    tests.iter().all(|a| test_miller_rabin(n, *a))
}

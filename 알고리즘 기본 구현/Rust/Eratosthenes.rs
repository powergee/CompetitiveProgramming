fn primes(last: usize) -> Vec<usize> {
    if last < 2 {
        return vec![];
    }

    let mut is_prime = vec![true; last + 1];
    is_prime[0] = false;
    is_prime[1] = false;
    let mut div = 2;

    while div * div <= last {
        if is_prime[div] {
            for i in (div * div..=last).step_by(div) {
                is_prime[i] = false;
            }
        }
        div += 1;
    }

    is_prime
        .into_iter()
        .enumerate()
        .skip(2)
        .filter_map(|(x, p)| if p { Some(x) } else { None })
        .collect()
}
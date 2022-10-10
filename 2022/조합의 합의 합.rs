fn main() {
    let mut buf = String::new();
    let _ = std::io::stdin().read_line(&mut buf).unwrap();
    let m = buf.trim().parse().unwrap();

    let modulo = 1000000007;
    let driver = &mut Combination::new(2*m, modulo);
    let mut answer = 0;

    for n in 3..=m {
        answer = (answer + driver.comb(2*n, n)) % modulo;
    }
    println!("{answer}");
}

struct Combination {
    fact: Vec<Option<u64>>,
    modulo: u64
}

impl Combination {
    fn new(max: usize, modulo: u64) -> Combination {
        Combination {
            fact: vec![None; max+1],
            modulo
        }
    }

    fn factorial(&mut self, n: usize) -> u64 {
        if n == 0 {
            1
        } else if let Some(result) = self.fact[n] {
            result
        } else {
            let result = (self.factorial(n-1)*(n as u64)) % self.modulo;
            self.fact[n] = Some(result);
            result
        }
    }

    fn pow_mod(&self, val: u64, exp: u64) -> u64 {
        if val == 0 {
            0
        } else if exp == 0 {
            1
        } else {
            let pow = self.pow_mod(val, exp/2);
            (pow*pow % self.modulo) * if exp % 2 == 0 { 1 } else { val } % self.modulo
        }
    }

    fn mod_inverse(&self, val: u64) -> u64 {
        self.pow_mod(val, self.modulo-2)
    }

    fn comb(&mut self, n: usize, k: usize) -> u64 {
        if n < k {
            0
        } else {
            let num = self.factorial(n);
            let den = (self.factorial(n-k)*self.factorial(k)) % self.modulo;
            let den = self.mod_inverse(den);
            (num * den) % self.modulo
        }
    }
}
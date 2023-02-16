pub struct CombCalc {
    fact_dp: Vec<usize>,
    bound: usize,
}

impl CombCalc {
    pub fn new(size: usize, bound: usize) -> Self {
        let mut fact_dp = Vec::with_capacity(size + 1);
        fact_dp.push(1);
        for i in 1..=size {
            fact_dp.push((*fact_dp.last().unwrap() * i) % bound);
        }
        Self { fact_dp, bound }
    }

    pub fn comb(&self, n: usize, k: usize) -> usize {
        if n < k {
            return 0;
        }
        (self.fact_dp[n] * self.mod_inverse((self.fact_dp[n - k] * self.fact_dp[k]) % self.bound))
            % self.bound
    }

    pub fn homo_comb(&self, n: usize, k: usize) -> usize {
        self.comb(n + k - 1, n - 1)
    }

    pub fn catalan(&self, n: usize) -> usize {
        (self.comb(2 * n, n) * self.mod_inverse(n + 1)) % self.bound
    }

    fn mod_pow(&self, val: usize, exp: usize) -> usize {
        if val == 0 {
            return 0;
        } else if exp == 0 {
            return 1;
        }
        let pow = self.mod_pow(val, exp / 2);
        (((pow * pow) % self.bound) * (if exp % 2 == 0 { 1 } else { val })) % self.bound
    }

    fn mod_inverse(&self, val: usize) -> usize {
        self.mod_pow(val, self.bound - 2)
    }
}
using System;
using System.Linq;

namespace Σ {
    class Fraction {
        const long MOD = 1000000007;
        private long value;

        public Fraction(long num, long den) {
            long gcd = GetGCD(num, den);
            num /= gcd;
            den /= gcd;
            value = (num * GetModInverse(den)) % MOD;
        }

        private Fraction(long value) {
            this.value = value;
        }

        private long GetModPow(long val, long exp) {
            if (val == 0) {
                return 0;
            } else if (exp == 0) {
                return 1;
            } else {
                long pow = GetModPow(val, exp/2);
                return (((pow * pow) % MOD) * (exp%2 == 0 ? 1 : val)) % MOD;
            }
        }

        private long GetModInverse(long val) {
            return GetModPow(val, MOD-2);
        }

        private long GetGCD(long a, long b) {
            return (b == 0 ? a : GetGCD(b, a%b));
        }

        public static Fraction operator+(Fraction f1,  Fraction f2) {
            return new Fraction((f1.value + f2.value) % MOD);
        }

        public override string ToString() {
            return value.ToString();
        }
    }

    class Program {
        static Fraction GetInput() {
            var tokens = Console.ReadLine().Split().Select(long.Parse).ToArray();
            return new Fraction(tokens[1], tokens[0]);
        }

        static void Main(string[] args) {
            int n = int.Parse(Console.ReadLine());

            Fraction sum = GetInput();
            for (int i = 1; i < n; ++i) {
                sum += GetInput();
            }

            Console.WriteLine(sum);
        }
    }
}

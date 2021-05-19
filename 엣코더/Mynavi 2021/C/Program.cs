using System;

namespace C {
    class Program {
        static long Factorial(int n) {
            long result = 1;
            for (int i = 1; i <= n; ++i) {
                result *= i;
            }
            return result;
        }

        static long Comb(int n, int k) {
            if (n < k) {
                return 0;
            }

            return Factorial(n) / (Factorial(k) * Factorial(n-k));
        }

        static long Pow(int n, int e) {
            long result = 1;
            for (int i = 1; i <= e; ++i) {
                result *= n;
            }
            return result;
        }

        static long CountPerm(int k) {
            long result = 0;
            for (int a = 1; a <= k; ++a) {
                for (int b = 1; b <= k; ++b) {
                    for (int c = 1; c <= k; ++c) {
                        for (int d = 1; d <= k; ++d) {
                            bool valid = true;
                            for (int i = 0; i < k; ++i) {
                                if (a != i+1 && b != i+1 && c != i+1 && d != i+1) {
                                    valid = false;
                                    break;
                                }
                            }
                            if (valid) {
                                ++result;
                            }
                        }
                    }
                }
            }
            return result;
        }

        static void Main(string[] args) {
            string input = Console.ReadLine();

            int c = 0;
            int n = 0;

            foreach (char ch in input) {
                if (ch == 'o') {
                    c++;
                } else if (ch == '?') {
                    n++;
                }
            }

            long answer;
            long p4 = CountPerm(4);
            long p3 = CountPerm(3);
            long p2 = CountPerm(2);
            long p1 = CountPerm(1);

            if (c > 4) {
                answer = 0;
            } else if (c == 4) {
                answer = p4;
            } else if (c == 3) {
                answer = p3 + p4*n;
            } else if (c == 2) {
                answer = p2 + p3*n + p4*Comb(n, 2);
            } else if (c == 1) {
                answer = p1 + p2*n + p3*Comb(n, 2) + p4*Comb(n, 3);
            } else {
                answer = p1*n + p2*Comb(n, 2) + p3*Comb(n, 3) + p4*Comb(n, 4);
            }

            Console.WriteLine(answer);
        }
    }
}

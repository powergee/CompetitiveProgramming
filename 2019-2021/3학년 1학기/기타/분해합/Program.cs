using System;
using static System.Console;

namespace 분해합 {
    class Program {
        static int getSum(int val) {
            int result = val;
            while (val > 0) {
                result += val % 10;
                val /= 10;
            }

            return result;
        }

        static void Main(string[] args) {
            int n = int.Parse(ReadLine());
            int result = 0;
            for (int i = 1; i <= n; ++i) {
                if (getSum(i) == n) {
                    result = i;
                    break;
                }
            }

            WriteLine(result);
        }
    }
}

using System;
using System.Linq;

namespace 문자열과_점수 {
    class Program {
        static int a, b, c;
        static string s, t;
        static int[,] dp;

        static int GetMaxScore(int sIdx, int tIdx) {
            if (sIdx == dp.GetLength(0)) {
                return (dp.GetLength(1) - tIdx) * b;
            } else if (tIdx == dp.GetLength(1)) {
                return (dp.GetLength(0) - sIdx) * b;
            }

            if (dp[sIdx, tIdx] != int.MinValue) {
                return dp[sIdx, tIdx];
            }

            ref int result = ref dp[sIdx, tIdx];
            if (s[sIdx] == t[tIdx]) {
                result = Math.Max(result, a + GetMaxScore(sIdx+1, tIdx+1));
            } else {
                result = Math.Max(result, c + GetMaxScore(sIdx+1, tIdx+1));
            }

            result = Math.Max(result, b + GetMaxScore(sIdx, tIdx+1));
            result = Math.Max(result, b + GetMaxScore(sIdx+1, tIdx));

            return result;
        }

        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            (a, b, c) = (tokens[0], tokens[1], tokens[2]);

            s = Console.ReadLine();
            t = Console.ReadLine();
            
            dp = new int[s.Length, t.Length];
            for (int i = 0; i < s.Length; ++i) {
                for (int j = 0; j < t.Length; ++j) {
                    dp[i, j] = int.MinValue;
                }
            }
            Console.WriteLine(GetMaxScore(0, 0));
        }
    }
}

using System;
using System.Linq;

namespace D {
    class Program {
        static int h, w;
        static int[,] score;
        static int[,] dp;

        static bool isValidPos(int r, int c) {
            return 0 <= r && r < h && 0 <= c && c < w;
        }

        static int getMaxDiff(int r, int c) {
            ref int result = ref dp[r, c];
            if (result != int.MinValue) {
                return result;
            }

            if (isValidPos(r+1, c)) {
                result = Math.Max(result, -getMaxDiff(r+1, c) + score[r+1, c]);
            }
            if (isValidPos(r, c+1)) {
                result = Math.Max(result, -getMaxDiff(r, c+1) + score[r, c+1]);
            }
            if (result == int.MinValue) {
                result = 0;
            }

            return result;
        }

        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            (h, w) = (tokens[0], tokens[1]);
            score = new int[h, w];
            for (int r = 0; r < h; ++r) {
                string line = Console.ReadLine();
                for (int c = 0; c < w; ++c) {
                    score[r, c] = (line[c] == '+' ? 1 : -1);
                }
            }

            dp = new int[h, w];
            for (int r = 0; r < h; ++r) {
                for (int c = 0; c < w; ++c) {
                    dp[r, c] = int.MinValue;
                }
            }

            int diff = getMaxDiff(0, 0);
            if (diff == 0) {
                Console.WriteLine("Draw");
            } else if (diff > 0) {
                Console.WriteLine("Takahashi");
            } else {
                Console.WriteLine("Aoki");
            }
        }
    }
}

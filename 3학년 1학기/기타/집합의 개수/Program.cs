using System;
using System.Linq;
using System.Collections.Generic;

namespace 집합의_개수 {
    class Program {
        static readonly int MOD = 1000000;
        static int t, a, s, b;
        static int[] arr;
        static List<KeyValuePair<int, int>> counts;
        static long[,] dp;

        static long countCases(int start, int need) {
            if (counts.Count == start) {
                if (need == 0) {
                    return 1;
                } else {
                    return 0;
                }
            }

            ref long result = ref dp[start, need];
            if (dp[start, need] != -1) {
                return dp[start, need];
            }

            result = 0;
            for (int use = 0; use <= Math.Min(counts[start].Value, need); ++use) {
                result += countCases(start+1, need-use);
                result %= MOD;
            }

            return result;
        }

        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            (t, a, s, b) = (tokens[0], tokens[1], tokens[2], tokens[3]);
            
            arr = Console.ReadLine().Split().Select(int.Parse).ToArray();
            SortedDictionary<int, int> countDict = new SortedDictionary<int, int>();
            foreach (int v in arr) {
                if (countDict.ContainsKey(v)) {
                    countDict[v] += 1;
                } else {
                    countDict[v] = 1;
                }
            }
            counts = new List<KeyValuePair<int, int>>();
            foreach (var pair in countDict) {
                counts.Add(pair);
            }

            dp = new long[counts.Count, b+1];
            for (int i = 0; i < counts.Count; ++i) {
                for (int j = 0; j < b+1; ++j) {
                    dp[i, j] = -1;
                }
            }
            long answer = 0;
            for (int i = s; i <= b; ++i) {
                answer += countCases(0, i);
                answer %= MOD;
            }
            Console.WriteLine(answer);
        }
    }
}

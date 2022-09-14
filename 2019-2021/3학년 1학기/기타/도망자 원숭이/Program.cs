using System;
using System.Linq;
using System.IO;

namespace 도망자_원숭이 {
    public record PivotVertex(int Number, int Resist);

    class Program {

        static void Main(string[] args) {
            var tokens = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
            var (n, m, q) = (tokens[0], tokens[1], tokens[2]);
            var times = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
            
            long[,] total = new long[n+1, n+1];
            long[,] dist = new long[n+1, n+1];

            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    total[i, j] = int.MaxValue;
                    dist[i, j] = int.MaxValue;
                }
                total[i, i] = times[i-1];
                dist[i, i] = 0;
            }

            for (int i = 0; i < m; ++i) {
                tokens = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
                var (s, e, c) = (tokens[0], tokens[1], tokens[2]);
                dist[s, e] = Math.Min(dist[s, e], c);
                dist[e, s] = Math.Min(dist[e, s], c);
            }

            PivotVertex[] pivots = new PivotVertex[n];
            for (int i = 1; i <= n; ++i) {
                pivots[i-1] = new PivotVertex(i, times[i-1]);
            }
            
            Array.Sort(pivots, (p1, p2) => p1.Resist.CompareTo(p2.Resist));

            foreach (var k in pivots) {
                foreach (var i in pivots) {
                    foreach (var j in pivots) {
                        int ni = i.Number, nj = j.Number, nk = k.Number;
                        dist[ni, nj] = Math.Min(dist[ni, nj], dist[ni, nk] + dist[nk, nj]);
                        total[ni, nj] = Math.Min(total[ni, nj], dist[ni, nj] + Math.Max(k.Resist, Math.Max(i.Resist, j.Resist)));
                    }
                }
            }

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                while (q-- > 0) {
                    tokens = Console.ReadLine().Trim().Split().Select(int.Parse).ToArray();
                    var (s, e) = (tokens[0], tokens[1]);
                    if (total[s, e] == int.MaxValue) {
                        writer.Write("-1\n");
                    } else {
                        writer.Write($"{total[s, e]}\n");
                    }
                }
            }
        }
    }
}

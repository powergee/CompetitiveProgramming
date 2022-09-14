using System;
using System.Linq;
using System.Collections.Generic;

namespace Ignition {
    class Edge {
        public int Start { get; set; }
        public int End { get; set; }
        public int Length { get; set; }

        public Edge(int s, int e, int l) {
            Start = s;
            End = e;
            Length = l;
        }
    }

    class Program {
        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (n, m) = (tokens[0], tokens[1]);

            List<Edge> edges = new();
            int[,] dist = new int[n+1, n+1];

            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= n; ++j) {
                    if (i == j) {
                        dist[i, j] = 0;
                    } else {
                        dist[i, j] = int.MaxValue / 2;
                    }
                }
            }

            for (int i = 0; i < m; ++i) {
                tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                var (s, e, l) = (tokens[0], tokens[1], tokens[2]*2);
                edges.Add(new Edge(s, e, l));
                dist[s, e] = Math.Min(dist[s, e], l);
                dist[e, s] = Math.Min(dist[e, s], l);
            }

            for (int k = 1; k <= n; ++k) {
                for (int i = 1; i <= n; ++i) {
                    for (int j = 1; j <= n; ++j) {
                        dist[i, j] = Math.Min(dist[i, j], dist[i, k] + dist[k, j]);
                    }
                }
            }

            int answer = int.MaxValue;
            for (int v = 1; v <= n; ++v) {
                int current = int.MinValue;
                foreach (Edge e in edges) {
                    int t1 = dist[v, e.Start];
                    int t2 = dist[v, e.End];
                    int min = Math.Min(t1, t2);
                    int max = Math.Max(t1, t2);
                    int spare = e.Length - (max - min);
                    current = Math.Max(current, max + Math.Max(spare / 2, 0));
                }
                answer = Math.Min(answer, current);
            }

            if (answer % 2 == 0) {
                Console.WriteLine($"{answer / 2}.0");
            } else {
                Console.WriteLine($"{answer / 2}.5");
            }
        }
    }
}

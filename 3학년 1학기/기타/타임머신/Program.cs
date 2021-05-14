using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace Solution {
    class Edge {
        public int Start { get; set; }
        public int End { get; set; }
        public long Cost { get; set; }
    }

    class Program {
        static (bool, long?[]) findDists(List<Edge> graph, int n, int start) {
            long?[] dist = new long?[n];
            Array.Fill(dist, null);
            dist[start] = 0;
            
            for (int i = 0; i < n-1; ++i) {
                foreach (Edge e in graph) {
                    if (dist[e.Start] != null && (dist[e.End] == null || dist[e.Start] + e.Cost < dist[e.End])) {
                        dist[e.End] = dist[e.Start] + e.Cost;
                    }
                }
            }

            bool hasNegCycle = false;
            foreach (Edge e in graph) {
                if (dist[e.Start] != null && (dist[e.End] == null || dist[e.Start] + e.Cost < dist[e.End])) {
                    hasNegCycle = true;
                }
            }

            if (hasNegCycle) {
                return (false, null);
            } else {
                return (true, dist);
            }
        }

        static void Main() {
            int n, m;
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            (n, m) = (tokens[0], tokens[1]);

            List<Edge> graph = new List<Edge>();
            for (int i = 0; i < m; ++i) {
                Edge e = new Edge();
                tokens = Console.ReadLine().Split(" ").Select(int.Parse).ToArray();
                (e.Start, e.End, e.Cost) = (tokens[0]-1, tokens[1]-1, tokens[2]);
                graph.Add(e);
            }

            var (hasAnswer, dist) = findDists(graph, n, 0);

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                if (hasAnswer) {
                    for (int i = 1; i < n; ++i) {
                        if (dist[i] == null) {
                            writer.Write("-1\n");
                        } else {
                            writer.Write($"{dist[i]}\n");
                        }
                    }
                } else {
                    writer.Write("-1\n");
                }
            }
        }
    }
}
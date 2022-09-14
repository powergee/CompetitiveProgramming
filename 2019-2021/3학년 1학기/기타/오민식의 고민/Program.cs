using System;
using System.Linq;
using System.Collections.Generic;
using System.IO;

namespace 오민식의_고민
{
    class Edge {
        public int Start { get; set; }
        public int End { get; set; }
        public long Cost { get; set; }
    }

    class Program
    {
        static void DFS(List<Edge> graph, bool[] visited, int start) {
            visited[start] = true;
            foreach (Edge e in graph) {
                if (e.Start == start && !visited[e.End]) {
                    DFS(graph, visited, e.End);
                }
            }
        }

        static (bool, long?) FindDists(List<Edge> graph, int[] benefits, int n, int start, int end) {
            long?[] dist = new long?[n];
            Array.Fill(dist, null);
            dist[start] = -benefits[start];
            
            for (int i = 0; i < n-1; ++i) {
                foreach (Edge e in graph) {
                    if (dist[e.Start] != null && (dist[e.End] == null || dist[e.Start] + e.Cost - benefits[e.End] < dist[e.End])) {
                        dist[e.End] = dist[e.Start] + e.Cost - benefits[e.End];
                    }
                }
            }

            bool[] visited = new bool[n];
            Array.Fill(visited, false);
            foreach (Edge e in graph) {
                if (dist[e.Start] != null && (dist[e.End] == null || dist[e.Start] + e.Cost - benefits[e.End] < dist[e.End])) {
                    DFS(graph, visited, e.End);
                }
            }

            if (dist[end] == null) {
                return (true, null);
            } else if (visited[end]) {
                return (false, null);
            } else {
                return (true, -dist[end]);
            }
        }

        static void Main(string[] args)
        {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (n, start, end, m) = (tokens[0], tokens[1], tokens[2], tokens[3]);

            List<Edge> graph = new List<Edge>();

            for (int i = 0; i < m; ++i) {
                tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                var (s, e, c) = (tokens[0], tokens[1], tokens[2]);
                graph.Add(new Edge() { Start = s, End = e, Cost = c });
            }

            int[] benefits = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (hasAnswer, dist) = FindDists(graph, benefits, n, start, end);

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                if (hasAnswer) {
                    if (dist == null) {
                        writer.Write("gg\n");
                    } else {
                        writer.Write($"{dist}\n");
                    }
                } else {
                    writer.Write("Gee\n");
                }
            }
        }
    }
}

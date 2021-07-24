using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace MCMFImplementation {
    class Edge {
        public int Source { get; }
        public int Destination { get; }
        public int Flow { get; private set; }
        public int Cost { get; private set; }
        public int Capacity { get; private set; }
        public Edge Opposite { get; set; }

        public int Spare => Capacity - Flow;

        public Edge(int src, int dst, int cost, int capa) {
            Source = src;
            Destination = dst;
            Flow = 0;
            Cost = cost;
            Capacity = capa;
        }

        public void AddFlow(int add) {
            Flow += add;
            if (Opposite != null) {
                Opposite.Flow -= add;
            }
        }
    }

    public record MCMF {
        public int Flowed { get; set; }
        public int TotalCost { get; set; }
    }

    class Graph {
        public static readonly int Inf = int.MaxValue/2;
        private List<Edge>[] graph;
        
        public Graph(int vertexCount) {
            graph = new List<Edge>[vertexCount];
            for (int i = 0; i < vertexCount; ++i) {
                graph[i] = new List<Edge>();
            }
        }

        public void AddEdge(int src, int dst, int cost, int capa) {
            Edge curr = new Edge(src, dst, cost, capa);
            Edge oppo = new Edge(dst, src, -cost, 0);
            curr.Opposite = oppo;
            oppo.Opposite = curr;

            graph[src].Add(curr);
            graph[dst].Add(oppo);
        }

        private List<Edge> FindAugPath(int src, int dst) {
            Edge[] prev = new Edge[graph.Length];
            int[] dist = new int[graph.Length];
            bool[] inQueue = new bool[graph.Length];
            Array.Fill(dist, Inf);
            Queue<int> q = new();

            dist[src] = 0;
            inQueue[src] = true;
            q.Enqueue(src);

            while (q.Count > 0) {
                int u = q.Dequeue();
                inQueue[u] = false;
                
                foreach (Edge e in graph[u]) {
                    if (e.Spare <= 0) {
                        continue;
                    }
                    int v = e.Destination;
                    if (dist[u] + e.Cost < dist[v]) {
                        dist[v] = dist[u] + e.Cost;
                        prev[v] = e;
                        if (!inQueue[v]) {
                            inQueue[v] = true;
                            q.Enqueue(v);
                        }
                    }
                }
            }

            if (prev[dst] == null) {
                return null;
            }

            List<Edge> path = new();
            for (Edge e = prev[dst]; e != null; e = prev[e.Source]) {
                path.Add(e);
            }

            return path;
        }

        public MCMF GetMinCostMaxFlow(int src, int dst) {
            MCMF result = new MCMF { Flowed = 0, TotalCost = 0 };
            List<Edge> path;

            while ((path = FindAugPath(src, dst)) != null) {
                int add = int.MaxValue;
                int costSum = 0;

                foreach (Edge e in path) {
                    add = Math.Min(add, e.Spare);
                }
                foreach (Edge e in path) {
                    e.AddFlow(add);
                    costSum += e.Cost;
                }

                result.Flowed += add;
                result.TotalCost += costSum * add;
            }

            return result;
        }
    }

    public record Line(int Axis, int Start, int End, int Weight);

    class Program {
        static void Swap(ref int a, ref int b) {
            int t = a;
            a = b;
            b = t;
        }

        static void Main(string[] args) {
            int T = int.Parse(Console.ReadLine());
            StreamWriter writer = new StreamWriter(Console.OpenStandardOutput());

            while (T-- > 0) {
                var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                var (n, m) = (tokens[0], tokens[1]);

                int vertexCount = n+m+3;
                int src = vertexCount-2;
                int dst = vertexCount-1;
                Graph graph = new Graph(vertexCount);
                Line[] horizontal = new Line[n+1];
                Line[] vertical = new Line[m+1];

                for (int i = 1; i <= n; ++i) {
                    tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                    var (x1, y1, x2, y2, w) = (tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
                    if (x2 < x1) {
                        Swap(ref x1, ref x2);
                    }
                    horizontal[i] = new Line(y1, x1, x2, w);
                    graph.AddEdge(src, i, 0, 1);
                }

                for (int i = 1; i <= m; ++i) {
                    tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                    var (x1, y1, x2, y2, w) = (tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
                    if (y2 < y1) {
                        Swap(ref y1, ref y2);
                    }
                    vertical[i] = new Line(x1, y1, y2, w);
                    graph.AddEdge(n+i, dst, 0, 1);
                }

                for (int i = 1; i <= n; ++i) {
                    for (int j = 1; j <= m; ++j) {
                        Line h = horizontal[i];
                        Line v = vertical[j];

                        if (h.Start <= v.Axis && v.Axis <= h.End &&
                            v.Start <= h.Axis && h.Axis <= v.End) {
                            graph.AddEdge(i, n+j, -(h.Weight*v.Weight), 1);
                        }
                    }
                }

                MCMF result = graph.GetMinCostMaxFlow(src, dst);
                writer.WriteLine($"{result.Flowed} {-result.TotalCost}");
            }
            writer.Close();
        }
    }
}

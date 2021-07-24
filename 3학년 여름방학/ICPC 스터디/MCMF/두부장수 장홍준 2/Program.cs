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
        static int[,] priceTable = {
            { 10, 8, 7, 5, 0, 1 },
            {  8, 6, 4, 3, 0, 1 },
            {  7, 4, 3, 2, 0, 1 },
            {  5, 3, 2, 2, 0, 1 },
            {  0, 0, 0, 0, 0, 0 },
            {  1, 1, 1, 1, 0, 0 },
        };

        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (n, m) = (tokens[0], tokens[1]);

            int vertexCount = n*m+3;
            int src = vertexCount-3;
            int srcNeck = vertexCount-2;
            int dst = vertexCount-1;
            Graph graph = new Graph(vertexCount);

            string[] map = new string[n];
            for (int i = 0; i < n; ++i) {
                map[i] = Console.ReadLine();
            }

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    char c1 = map[i][j], c2;
                    int n1 = i*m+j, n2;
                    bool even = (i+j) % 2 == 0;

                    if (j+1 < m) {
                        c2 = map[i][j+1];
                        n2 = i*m+j+1;
                        if (even) {
                            graph.AddEdge(n1, n2, -priceTable[c1-'A', c2-'A'], 1);
                        } else {
                            graph.AddEdge(n2, n1, -priceTable[c1-'A', c2-'A'], 1);
                        }
                    }

                    if (i+1 < n) {
                        c2 = map[i+1][j];
                        n2 = (i+1)*m+j;
                        if (even) {
                            graph.AddEdge(n1, n2, -priceTable[c1-'A', c2-'A'], 1);
                        } else {
                            graph.AddEdge(n2, n1, -priceTable[c1-'A', c2-'A'], 1);
                        }
                    }

                    if (even) {
                        graph.AddEdge(srcNeck, n1, 0, 1);
                    } else {
                        graph.AddEdge(n1, dst, 0, 1);
                    }
                }
            }

            graph.AddEdge(src, srcNeck, 0, n*m/2);
            graph.AddEdge(srcNeck, dst, 0, Graph.Inf);

            Console.WriteLine(-graph.GetMinCostMaxFlow(src, dst).TotalCost);
        }
    }
}

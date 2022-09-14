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

    class Program {
        static void Main(string[] args) {
            StreamWriter writer = new StreamWriter(Console.OpenStandardOutput());
            string init;

            while ((init = Console.ReadLine()) != null) {
                var tokens = init.Split().Select(int.Parse).ToArray();
                var (v, e) = (tokens[0], tokens[1]);

                int vertexCount = v*2+2;
                Graph graph = new Graph(vertexCount);

                for (int i = 0; i < e; ++i) {
                    tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                    var (a, b, c) = (tokens[0], tokens[1], tokens[2]);
                    graph.AddEdge(a*2+1, b*2, c, 1);
                }

                for (int i = 1; i <= v; ++i) {
                    if (i == 1 || i == v) {
                        graph.AddEdge(i*2, i*2+1, 0, 2);
                    } else {
                        graph.AddEdge(i*2, i*2+1, 0, 1);
                    }
                }

                writer.WriteLine(graph.GetMinCostMaxFlow(1*2, v*2+1).TotalCost);
            }

            writer.Close();
        }
    }
}

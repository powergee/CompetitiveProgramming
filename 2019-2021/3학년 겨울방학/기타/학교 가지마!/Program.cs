using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace 학교_가지마 {
    class Endpoint {
        public int Number { get; init; }
        public List<DirectedEdge> Outgoing { get; set; }

        public Endpoint(int num) {
            Number = num;
            Outgoing = new List<DirectedEdge>();
        }
    }

    class DirectedEdge {
        public static readonly DirectedEdge Dummy = new DirectedEdge();

        public Endpoint Source { get; init; }
        public Endpoint Destination { get; init; }
        public long Capacity { get; set; } = 0;
        public long Flow { get; private set; } = 0;
        public DirectedEdge Inverse { get; private set; }

        public long Spare => Capacity - Flow;

        public DirectedEdge(Endpoint src, Endpoint dst, long capacity) {
            Source = src;
            Destination = dst;
            Capacity = capacity;
            Inverse = new DirectedEdge(this);

            Source.Outgoing.Add(this);
        }

        public DirectedEdge(Vertex src, Vertex dst, long capacity)
            : this(src.Out, dst.In, capacity) {}

        private DirectedEdge(DirectedEdge inverse) {
            Source = inverse.Destination;
            Destination = inverse.Source;
            Inverse = inverse;

            Source.Outgoing.Add(this);
        }

        private DirectedEdge() {}

        public void AddFlow(long add) {
            Flow += add;
            Inverse.Flow -= add;
        }
    }

    class Vertex {
        public int Number { get; init; }
        public Endpoint In { get; init; }
        public Endpoint Out { get; init; }
        public DirectedEdge InnerEdge { get; init; }

        public Vertex(int num, long capacity = long.MaxValue/2) {
            Number = num;
            In = new Endpoint(num*2);
            Out = new Endpoint(num*2+1);
            InnerEdge = new DirectedEdge(In, Out, capacity);
        }
    }

    class Graph {
        private Vertex[] vertices;

        public Graph(int verCount) {
            vertices = new Vertex[verCount];
            for (int i = 0; i < verCount; ++i) {
                vertices[i] = new Vertex(i);
            }
        }

        public void SetInnerCapacity(int verIdx, long capacity) {
            vertices[verIdx].InnerEdge.Capacity = capacity;
        }

        public void AddEdge(int src, int dst, long capacity) {
            new DirectedEdge(vertices[src], vertices[dst], capacity);
        }

        private bool FindAugmentingPath(Vertex src, Vertex dst, out DirectedEdge[] prev) {
            prev = new DirectedEdge[vertices.Length*2];
            Queue<Endpoint> q = new Queue<Endpoint>();
            q.Enqueue(src.In);
            prev[src.In.Number] = DirectedEdge.Dummy;

            while (q.Count > 0) {
                var curr = q.Dequeue();

                foreach (var edge in curr.Outgoing) {
                    if (0 < edge.Spare && prev[edge.Destination.Number] == null) {
                        q.Enqueue(edge.Destination);
                        prev[edge.Destination.Number] = edge;
                    }
                    if (prev[dst.Out.Number] != null) {
                        return true;
                    }
                }
            }

            return false;
        }

        public long EdmondsKarp(int src, int dst) {
            Vertex vs = vertices[src], vd = vertices[dst];
            long result = 0;
            DirectedEdge[] prev;

            while (FindAugmentingPath(vs, vd, out prev)) {
                long add = long.MaxValue;

                for (var edge = prev[vd.Out.Number]; edge != DirectedEdge.Dummy; edge = prev[edge.Source.Number]) {
                    add = Math.Min(add, edge.Spare);
                }
                for (var edge = prev[vd.Out.Number]; edge != DirectedEdge.Dummy; edge = prev[edge.Source.Number]) {
                    edge.AddFlow(add);
                }

                result += add;
            }

            return result;
        }
    }

    class Program {
        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (n, m) = (tokens[0], tokens[1]);
            int verCount = n*m;
            Graph g = new Graph(verCount);
            string[] map = new string[n];
            
            for (int i = 0; i < n; ++i) {
                map[i] = Console.ReadLine();
            }

            int src = 0, dst = 0;
            int srcRow = 0, srcCol = 0;
            int dstRow = 0, dstCol = 0;

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (map[i][j] == '#') {
                        continue;
                    }
                    int currIdx = i*m + j;

                    int[] dr = { 0, 0, 1, -1 };
                    int[] dc = { 1, -1, 0, 0 };
                    for (int k = 0; k < 4; ++k) {
                        int nr = dr[k] + i;
                        int nc = dc[k] + j;
                        int nextIdx = nr*m + nc;
                        if (0 <= nr && nr < n && 0 <= nc && nc < m && map[nr][nc] != '#') {
                            g.AddEdge(currIdx, nextIdx, 1);
                        }
                    }

                    switch (map[i][j]) {
                        case 'H':
                            dst = currIdx;
                            dstRow = i; dstCol = j;
                            break;
                        case 'K':
                            src = currIdx;
                            srcRow = i; srcCol = j;
                            break;
                        default:
                            g.SetInnerCapacity(currIdx, 1);
                            break;
                    }
                }
            }
            
            if (Math.Abs(srcRow-dstRow) + Math.Abs(srcCol-dstCol) == 1) {
                Console.WriteLine("-1");
            } else {
                Console.WriteLine(g.EdmondsKarp(src, dst));
            }
        }
    }
}

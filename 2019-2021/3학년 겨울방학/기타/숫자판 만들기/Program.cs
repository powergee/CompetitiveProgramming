using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace 숫자판_만들기 {
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

        public void ClearFlow() {
            Flow = 0;
            Inverse.Flow = 0;
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

        public long GetInnerFlow(int verIdx) {
            return vertices[verIdx].InnerEdge.Flow;
        }

        public void SetInnerCapacity(int verIdx, long capacity) {
            vertices[verIdx].InnerEdge.Capacity = capacity;
        }

        public void AddEdge(int src, int dst, long capacity = long.MaxValue/2) {
            new DirectedEdge(vertices[src], vertices[dst], capacity);
        }

        private bool FindAugmentingPath(Vertex src, Vertex dst, ref DirectedEdge[] prev) {
            Array.Fill(prev, null);
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
            ClearFlows();
            Vertex vs = vertices[src], vd = vertices[dst];
            DirectedEdge[] prev = new DirectedEdge[vertices.Length * 2];
            long result = 0;

            while (FindAugmentingPath(vs, vd, ref prev)) {
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

        public void ClearFlows() {
            foreach (var v in vertices) {
                foreach (var e in v.In.Outgoing) {
                    e.ClearFlow();
                }
                foreach (var e in v.Out.Outgoing) {
                    e.ClearFlow();
                }
            }
        }
    }

    class Program {
        static void Main(string[] args) {
            int n = int.Parse(Console.ReadLine());
            var rows = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var cols = Console.ReadLine().Split().Select(int.Parse).ToArray();
            int sum = rows.Sum();

            // [0, n*n) = 숫자판의 각 자리
            // [n*n, n*n + n) = 행 별 합
            // [n*n + n, n*n + 2*n) = 열 별 합
            // n*n + 2*n = Global Source
            // n*n + 2*n + 1 = Global Destination
            Graph g = new Graph(n*n + 2*n + 2);
            Func<int, int, int> ToIdx = (r, c) => r*n + c;
            int src = n*n + 2*n;
            int dst = n*n + 2*n + 1;
            
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    // 행 별 합
                    g.AddEdge(n*n+i, ToIdx(i, j));
                    // 열 별 합
                    g.AddEdge(ToIdx(i, j), n*n+n+j);
                }
            }

            for (int i = 0; i < n; ++i) {
                g.SetInnerCapacity(n*n + i, rows[i]);
                g.SetInnerCapacity(n*n + n + i, cols[i]);

                // Global Source와 행 별 합 Vertices 연결
                g.AddEdge(src, n*n + i);
                // 열 별 합 Vertices와 Global Destination 연결
                g.AddEdge(n*n + n + i, dst);
            }
            
            long left = 0, right = 10000;
            while (left < right) {
                long mid = (left+right) / 2;
                
                for (int i = 0; i < n*n; ++i) {
                    g.SetInnerCapacity(i, mid);
                }

                if (g.EdmondsKarp(src, dst) == sum) {
                    right = mid;
                } else {
                    left = mid+1;
                }
            }

            for (int i = 0; i < n*n; ++i) {
                g.SetInnerCapacity(i, left);
            }
            g.EdmondsKarp(src, dst);

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                writer.Write($"{left}\n");
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < n; ++j) {
                        writer.Write($"{g.GetInnerFlow(ToIdx(i, j))} ");
                    }
                    writer.Write("\n");
                }
            }
        }
    }
}

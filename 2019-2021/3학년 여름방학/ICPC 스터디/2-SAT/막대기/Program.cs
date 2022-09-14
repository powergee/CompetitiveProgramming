using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace 막대기 {
    using SCC = List<Vertex>;

    public record Point(long X, long Y) {
        public static bool operator<=(Point p1, Point p2) {
            if (p1.X != p2.X) {
                return p1.X <= p2.X;
            }
            return p1.Y <= p2.Y;
        }

        public static bool operator>=(Point p1, Point p2) {
            if (p1.X != p2.X) {
                return p1.X >= p2.X;
            }
            return p1.Y >= p2.Y;
        }

        public static (Point, Point) SortPair(Point p1, Point p2) {
            return p1 <= p2 ? (p1, p2) : (p2, p1);
        }
    }

    public record Line(Point P1, Point P2) {
        private int CCW(Point p1, Point p2, Point p3) {
            long op = p1.X*p2.Y + p2.X*p3.Y + p3.X*p1.Y
                    - p1.Y*p2.X - p2.Y*p3.X - p3.Y*p1.X;
            if (op < 0) {
                return 1;
            } else if (op == 0) {
                return 0;
            } else {
                return -1;
            }
        }

        public bool IsCrossed(Line other) {
            int ab = CCW(P1, P2, other.P1) * CCW(P1, P2, other.P2);
            int cd = CCW(other.P1, other.P2, P1) * CCW(other.P1, other.P2, P2);

            if (ab == 0 && cd == 0) {
                var (a, b) = Point.SortPair(P1, P2);
                var (c, d) = Point.SortPair(other.P1, other.P2);
                return c <= b && a <= d;
            }
            return ab <= 0 && cd <= 0;
        }
    }

    class Vertex : IComparable<Vertex> {
        public int Number { get; init; }
        public int? VisitedID { get; set; }
        public bool Finished { get; set; }
        public List<Vertex> Neighbourhood { get; private set; }

        public Vertex(int num) {
            Number = num;
            Neighbourhood = new List<Vertex>();
        }

        public int CompareTo(Vertex v) {
            return Number.CompareTo(v.Number);
        }
    }

    class Graph {
        private Vertex[] vertices;

        public Graph(int vertexCount) {
            vertices = new Vertex[vertexCount];
            for (int i = 0; i < vertexCount; ++i) {
                vertices[i] = new Vertex(i);
            }
        }

        public void AddEdge(int s, int e) {
            vertices[s].Neighbourhood.Add(vertices[e]);
        }

        public List<SCC> FindSCCs() {
            foreach (Vertex v in vertices) {
                v.VisitedID = null;
                v.Finished = false;
            }

            List<SCC> sccList = new List<SCC>();
            Stack<Vertex> recStack = new Stack<Vertex>();
            int id = 0;

            foreach (Vertex v in vertices) {
                if (v.VisitedID == null) {
                    FindParentByDFS(v, ref id, sccList, recStack);
                }
            }

            return sccList;
        }

        private Vertex FindParentByDFS(Vertex start, ref int id, List<SCC> sccList, Stack<Vertex> recStack) {
            Vertex parent = start;
            start.VisitedID = id++;
            recStack.Push(start);

            foreach (Vertex next in start.Neighbourhood) {
                if (next.VisitedID == null) {
                    Vertex found = FindParentByDFS(next, ref id, sccList, recStack);
                    parent = (found.VisitedID < parent.VisitedID ? found : parent);
                } else if (!next.Finished) {
                    parent = (next.VisitedID < parent.VisitedID ? next : parent);
                }
            }

            if (parent == start) {
                SCC scc = new SCC();
                Vertex top;
                do {
                    top = recStack.Pop();
                    top.Finished = true;
                    scc.Add(top);
                } while (top != parent);
                sccList.Add(scc);
            }

            return parent;
        }
    }

    class Program {
        static int ToIndex(int verRep) {
            bool neg = verRep < 0;
            int abs = (verRep < 0 ? -verRep : verRep);
            return (neg ? 2*abs+1 : 2*abs);
        }

        static int Not(int index) {
            return (index % 2 == 0 ? index+1 : index-1);
        }

        static void Main(string[] args) {
            int n = int.Parse(Console.ReadLine());
            Line[,] lines = new Line[n, 3];
            Graph g = new Graph(6*n);

            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < 3; ++j) {
                    var tokens = Console.ReadLine().Split().Select(long.Parse).ToArray();
                    var (x1, y1, x2, y2) = (tokens[0], tokens[1], tokens[2], tokens[3]);
                    lines[i, j] = new Line(new Point(x1, y1), new Point(x2, y2));

                    for (int k = 0; k < 3; ++k) {
                        if (j != k) {
                            g.AddEdge(ToIndex(3*i+j), Not(ToIndex(3*i+k)));
                        }
                    }
                }
            }

            for (int i = 0; i < 3*n; ++i) {
                for (int j = i+1; j < 3*n; ++j) {
                    if (lines[i/3, i%3].IsCrossed(lines[j/3, j%3])) {
                        g.AddEdge(Not(ToIndex(i)), ToIndex(j));
                        g.AddEdge(Not(ToIndex(j)), ToIndex(i));
                    }
                }
            }

            bool able = true;
            List<SCC> sccs = g.FindSCCs();
            foreach (SCC scc in sccs) {
                scc.Sort();
                for (int i = 0; i < scc.Count-1; ++i) {
                    if (scc[i].Number % 2 == 0 && scc[i].Number+1 == scc[i+1].Number) {
                        able = false;
                    }
                }
            }

            bool?[] assigned = new bool?[6*n];
            sccs.Reverse();
            if (able) {
                foreach (SCC scc in sccs) {
                    bool toAssign = false;
                    foreach (Vertex v in scc) {
                        if (assigned[v.Number] != null) {
                            toAssign = assigned[v.Number].Value;
                            break;
                        }
                    }

                    foreach (Vertex v in scc) {
                        assigned[v.Number] = toAssign;
                        assigned[Not(v.Number)] = !toAssign;
                    }
                }
            }

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                if (able) {
                    List<int> answers = new List<int>();
                    for (int i = 0; i < 6*n; i += 2) {
                        if (assigned[i].Value) {
                            answers.Add(i/2+1);
                        }
                    }
                    writer.WriteLine(answers.Count);
                    writer.WriteLine(String.Join(' ', answers));
                } else {
                    writer.WriteLine("-1");
                }
            }
        }
    }
}

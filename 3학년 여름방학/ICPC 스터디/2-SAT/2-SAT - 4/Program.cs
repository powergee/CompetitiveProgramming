using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace _2_SAT___4 {
    using SCC = List<Vertex>;

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
            return (neg ? 2*(abs-1)+1 : 2*(abs-1));
        }

        static int Not(int index) {
            return (index % 2 == 0 ? index+1 : index-1);
        }

        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (n, m) = (tokens[0], tokens[1]);
            Graph g = new Graph(2*n);

            for (int i = 0; i < m; ++i) {
                tokens = Console.ReadLine().Split().Select(int.Parse).Select(ToIndex).ToArray();
                var (a, b) = (tokens[0], tokens[1]);
                g.AddEdge(Not(a), b);
                g.AddEdge(Not(b), a);
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

            bool?[] assigned = new bool?[2*n];
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
                writer.WriteLine(able ? 1 : 0);
                if (able) {
                    for (int i = 0; i < 2*n; i += 2) {
                        writer.Write($"{(assigned[i].Value ? 1 : 0)} ");
                    }
                    writer.WriteLine();
                }
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace 아이돌 {
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
        static bool GetTestCase(out int n, out int m) {
            string line = Console.ReadLine();
            if (line == null) {
                (n, m) = (-1, -1);
                return false;
            }
            var tokens = line.Split().Select(int.Parse).ToArray();
            (n, m) = (tokens[0], tokens[1]);
            return true;
        }
        
        static int ToIndex(int verRep) {
            bool neg = verRep < 0;
            int abs = (verRep < 0 ? -verRep : verRep);
            return (neg ? 2*(abs-1)+1 : 2*(abs-1));
        }

        static int Not(int index) {
            return (index % 2 == 0 ? index+1 : index-1);
        }

        static void Main(string[] args) {
            int n, m;
            StreamWriter writer = new StreamWriter(Console.OpenStandardOutput());

            while (GetTestCase(out n, out m)) {
                Graph g = new Graph(2*n);

                for (int i = 0; i < m; ++i) {
                    var tokens = Console.ReadLine().Split().Select(int.Parse).Select(ToIndex).ToArray();
                    var (a, b) = (tokens[0], tokens[1]);
                    g.AddEdge(Not(a), b);
                    g.AddEdge(Not(b), a);
                }
                g.AddEdge(1, 0);

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

                writer.WriteLine(able ? "yes" : "no");
            }
            writer.Dispose();
        }
    }
}

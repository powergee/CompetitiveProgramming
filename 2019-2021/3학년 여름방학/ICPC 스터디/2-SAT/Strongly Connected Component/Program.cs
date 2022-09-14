using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace Strongly_Connected_Component {
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
        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (v, e) = (tokens[0], tokens[1]);
            Graph g = new Graph(v);

            for (int i = 0; i < e; ++i) {
                tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                var (a, b) = (tokens[0]-1, tokens[1]-1);
                g.AddEdge(a, b);
            }

            var result = g.FindSCCs();
            result.ForEach((scc) => {
                scc.Sort();
            });
            result.Sort((s1, s2) => {
                return s1.First().CompareTo(s2.First());
            });

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                writer.WriteLine(result.Count);
                foreach (SCC scc in result) {
                    foreach (Vertex ver in scc) {
                        writer.Write($"{ver.Number+1} ");
                    }
                    writer.WriteLine("-1");
                }
            }
        }
    }
}

using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace TV_Show_Game {
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
        static int ToIndex(int vertex) {
            return 2*(vertex-1);
        }

        static int Not(int index) {
            return (index % 2 == 0 ? index+1 : index-1);
        }
        
        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (k, n) = (tokens[0], tokens[1]);
            Graph g = new Graph(2*k);

            for (int i = 0; i < n; ++i) {
                var words = Console.ReadLine().Split();
                int[] nums = new int[3];
                bool[] preds = new bool[3];
                for (int j = 0; j < words.Length; j += 2) {
                    nums[j/2] = int.Parse(words[j]);
                    preds[j/2] = words[j+1][0] == 'R';
                }
                for (int p1 = 0; p1 < 3; ++p1) {
                    for (int p2 = 0; p2 < 3; ++p2) {
                        if (p1 != p2) {
                            int left = (preds[p1] ? Not(ToIndex(nums[p1])) : ToIndex(nums[p1]));
                            int right = (preds[p2] ? ToIndex(nums[p2]) : Not(ToIndex(nums[p2])));
                            g.AddEdge(left, right);
                        }
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

            bool?[] assigned = new bool?[2*k];
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
                    for (int i = 0; i < 2*k; i += 2) {
                        writer.Write((assigned[i].Value ? 'R' : 'B'));
                    }
                    writer.WriteLine();
                } else {
                    writer.WriteLine("-1");
                }
            }
        }
    }
}

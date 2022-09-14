using System;
using System.Linq;
using System.Collections.Generic;
using System.IO;

namespace 책_나눠주기 {
    class Query : IComparable<Query> {
        public int Start { get; set; }
        public int End { get; set; }

        public Query(int s, int e) {
            Start = s;
            End = e;
        }

        public int CompareTo(Query other) {
            if (End == other.End) {
                return Start.CompareTo(other.Start);
            }
            return End.CompareTo(other.End);
        }
    }

    class Program {
        static void Main(string[] args) {
            int T = int.Parse(Console.ReadLine());
            StreamWriter writer = new StreamWriter(Console.OpenStandardOutput());
            while (T-- > 0) {
                var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                var (n, m) = (tokens[0], tokens[1]);

                List<Query> queries = new List<Query>();
                for (int i = 0; i < m; ++i) {
                    tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                    var (s, e) = (tokens[0], tokens[1]);
                    queries.Add(new Query(s, e));
                }
                queries.Sort();
                
                int answer = 0;
                bool[] used = new bool[n+1];
                Array.Fill(used, false);
                foreach (var q in queries) {
                    for (int i = q.Start; i <= q.End; ++i) {
                        if (!used[i]) {
                            used[i] = true;
                            ++answer;
                            break;
                        }
                    }
                }

                writer.Write($"{answer}\n");
            }
            writer.Dispose();
        }
    }
}

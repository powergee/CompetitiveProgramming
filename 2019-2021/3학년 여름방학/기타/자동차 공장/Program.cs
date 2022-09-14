using System;
using System.Linq;
using System.Collections.Generic;
using System.IO;

namespace 자동차_공장 {
    class SegTree {
        public int Count;
        private List<long> tree;
        private List<long> lazy;

        public SegTree(List<long> original) {
            Count = original.Count;
            int treeHeight = (int)Math.Ceiling(Math.Log2(Count));
            int listSize = (1 << (treeHeight+1));
            tree = new List<long>(new long[listSize]);
            lazy = new List<long>(new long[listSize]);
            Initialize(1, 0, Count-1, original);
        }

        public long Query(int start, int end) {
            return Query(1, start, end, 0, Count-1);
        }

        public void Update(int start, int end, long add) {
            Update(add, 1, start, end, 0, Count-1);
        }

        private void Initialize(int index, int start, int end, List<long> original) {
            if (start == end) {
                tree[index] = original[start];
            } else {
                int mid = (start+end) / 2;
                Initialize(index*2, start, mid, original);
                Initialize(index*2+1, mid+1, end, original);
                tree[index] = tree[index*2] + tree[index*2+1];
            }
        }

        private void Propagate(int index, int start, int end) {
            if (lazy[index] != 0) {
                tree[index] += lazy[index] * (end-start+1);
                if (start < end) {
                    lazy[index*2] += lazy[index];
                    lazy[index*2+1] += lazy[index];
                }
                lazy[index] = 0;
            }
        }

        private long Query(int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
            Propagate(index, treeStart, treeEnd);

            if (reqStart <= treeStart && treeEnd <= reqEnd) {
                return tree[index];
            } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
                int treeMed = (treeStart + treeEnd) / 2;
                long left = Query(index*2, reqStart, reqEnd, treeStart, treeMed);
                long right = Query(index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
                return left + right;
            } else {
                return 0;
            }
        }

        private void Update(long add, int index, int reqStart, int reqEnd, int treeStart, int treeEnd) {
            Propagate(index, treeStart, treeEnd);

            if (reqStart <= treeStart && treeEnd <= reqEnd) {
                lazy[index] += add;
                Propagate(index, treeStart, treeEnd);
            } else if (treeStart <= reqEnd && reqStart <= treeEnd) {
                int treeMed = (treeStart + treeEnd) / 2;
                Update(add, index*2, reqStart, reqEnd, treeStart, treeMed);
                Update(add, index*2+1, reqStart, reqEnd, treeMed+1, treeEnd);
                tree[index] = tree[index*2] + tree[index*2+1];
            }
        }
    }

    class Range {
        public int Lower { get; }
        public int Upper { get; }

        public Range(int lower, int upper) {
            Lower = lower;
            Upper = upper;
        }
    }

    class Employee : IComparable<Employee> {
        public int ID { get; }
        public int Index { get; set; }
        public int Payment { get; }
        public int SeniorID { get; }
        public List<Employee> Juniors { get; }
        public Range IndexRange { get; set; }

        public Employee(int id, int payment, int seniorID) {
            ID = id;
            Index = -1;
            Payment = payment;
            SeniorID = seniorID;
            Juniors = new List<Employee>();
            IndexRange = null;
        }

        public int CompareTo(Employee other) {
            return Index.CompareTo(other.Index);
        }
    }

    class Program {
        static int Preorder(Employee node, int index, List<long> payments, Dictionary<int, int> indexDict) {
            node.Index = index;
            payments.Add(node.Payment);
            indexDict[node.ID] = index;
            int lower = index;
            int upper = index;

            foreach (Employee next in node.Juniors) {
                index = Preorder(next, index+1, payments, indexDict);
                upper = index;
            }

            node.IndexRange = new Range(lower, upper);
            return index;
        }

        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (n, m) = (tokens[0], tokens[1]);

            List<Employee> emps = new();
            int rootPay = int.Parse(Console.ReadLine());
            emps.Add(new Employee(1, rootPay, 0));

            for (int i = 2; i <= n; ++i) {
                tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                var (pay, senior) = (tokens[0], tokens[1]);
                emps.Add(new Employee(i, pay, senior));
            }

            foreach (var emp in emps) {
                if (emp.SeniorID != 0) {
                    emps[emp.SeniorID-1].Juniors.Add(emp);
                }
            }

            List<long> preorderPayment = new List<long>(n);
            Dictionary<int, int> indexDict = new Dictionary<int, int>();
            Preorder(emps[0], 0, preorderPayment, indexDict);
            emps.Sort();
            SegTree tree = new SegTree(preorderPayment);

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                for (int i = 0; i < m; ++i) {
                    string line = Console.ReadLine();
                    switch (line[0])
                    {
                        case 'p': {
                            tokens = line.Substring(2).Split().Select(int.Parse).ToArray();
                            var (senior, add) = (tokens[0], tokens[1]);
                            int index = indexDict[senior];
                            Range range = emps[index].IndexRange;
                            if (range.Lower < range.Upper) {
                                tree.Update(range.Lower+1, range.Upper, add);
                            }
                            break;
                        }

                        case 'u': {
                            int id = int.Parse(line.Substring(2));
                            int index = indexDict[id];
                            writer.WriteLine(tree.Query(index, index));
                            break;
                        }
                    }
                }
            }
        }
    }
}

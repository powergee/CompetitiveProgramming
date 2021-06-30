using System;
using System.Collections.Generic;
using System.Linq;
using System.IO;

namespace 구간_합_구하기_2 {
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

        public SegTree(int count) {
            Count = count;
            int treeHeight = (int)Math.Ceiling(Math.Log2(Count));
            int listSize = (1 << (treeHeight+1));
            tree = new List<long>(new long[listSize]);
            lazy = new List<long>(new long[listSize]);
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

    class Program {
        static void Main(string[] args) {
            var t = Console.ReadLine().Split().Select(long.Parse).ToArray();
            var (n, m, k) = (t[0], t[1], t[2]);

            List<long> origin = new List<long>((int)n);
            for (int i = 0; i < n; ++i) {
                origin.Add(long.Parse(Console.ReadLine()));
            }
            SegTree tree = new SegTree(origin);

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                for (int i = 0; i < m+k; ++i) {
                    t = Console.ReadLine().Split().Select(long.Parse).ToArray();
                    var (kind, left, right) = (t[0], t[1], t[2]);
                    left--; right--;

                    switch (kind)
                    {
                        case 1:
                            tree.Update((int)left, (int)right, t[3]);
                            break;
                        
                        case 2:
                            writer.WriteLine(tree.Query((int)left, (int)right));
                            break;
                    }
                }
            }
        }
    }
}

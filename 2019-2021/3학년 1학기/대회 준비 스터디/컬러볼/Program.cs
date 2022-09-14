using System;
using System.Linq;
using System.Collections.Generic;
using System.IO;

namespace 컬러볼 {
    class BallCollection {
        private SortedList<int, int> sizeCount;
        private List<int> sum;

        private int BinarySearch<T>(IList<T> list, T value) {
            var comp = Comparer<T>.Default;
            int lo = 0, hi = list.Count - 1;
            while (lo < hi) {
                    int m = (hi + lo) / 2;
                    if (comp.Compare(list[m], value) < 0) lo = m + 1;
                    else hi = m - 1;
            }
            if (comp.Compare(list[lo], value) < 0) lo++;
            return lo;
        }

        public BallCollection() {
            sizeCount = new SortedList<int, int>();
        }

        public void AddBall(int size) {
            if (sizeCount.ContainsKey(size)) {
                sizeCount[size]++;
            } else {
                sizeCount[size] = 1;
            }
        }

        public void BuildSum() {
            sum = new List<int>();
            sum.Add(0);
            foreach (var pair in sizeCount) {
                sum.Add(sum.Last() + pair.Key*pair.Value);
            }
        }

        public int sumSmaller(int s) {
            int found = BinarySearch(sizeCount.Keys, s);
            return sum[found];
        }
    }

    class Program {
        static void Main(string[] args) {
            int n = int.Parse(Console.ReadLine());
            BallCollection all = new BallCollection();
            Dictionary<int, BallCollection> bcDict = new Dictionary<int, BallCollection>();
            List<KeyValuePair<int, int>> balls = new List<KeyValuePair<int, int>>();

            for (int i = 0; i < n; ++i) {
                int color, size;
                var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                (color, size) = (tokens[0], tokens[1]);
                balls.Add(new KeyValuePair<int, int>(color, size));

                if (!bcDict.ContainsKey(color)) {
                    bcDict[color] = new BallCollection();
                }
                bcDict[color].AddBall(size);
                all.AddBall(size);
            }

            all.BuildSum();
            foreach (var pair in bcDict) {
                pair.Value.BuildSum();
            }

            using (StreamWriter writer = new StreamWriter(Console.OpenStandardOutput())) {
                foreach (var pair in balls) {
                    writer.Write($"{all.sumSmaller(pair.Value) - bcDict[pair.Key].sumSmaller(pair.Value)}\n");
                }
            }
        }
    }
}

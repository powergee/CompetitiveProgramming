using System;
using System.Linq;

namespace 스티커_붙이기 {
    class Module {
        private bool[,] isFilled;
        private int rows, cols;
        
        public Module(int rows, int cols) {
            isFilled = new bool[rows, cols];
            this.rows = rows;
            this.cols = cols;
        }

        public Module(int[][] rep) : this(rep.Length, rep[0].Length) {
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    isFilled[r, c] = (rep[r][c] == 1 ? true : false);
                }
            }
        }

        private bool IsAbleToEmbed(int dr, int dc, Module m) {
            for (int r = 0; r < m.rows; ++r) {
                for (int c = 0; c < m.cols; ++c) {
                    if (m.isFilled[r, c] && isFilled[dr+r, dc+c]) {
                        return false;
                    }
                }
            }
            return true;
        }

        private void Embed(int dr, int dc, Module m) {
            for (int r = 0; r < m.rows; ++r) {
                for (int c = 0; c < m.cols; ++c) {
                    isFilled[dr+r, dc+c] = isFilled[dr+r, dc+c] || m.isFilled[r, c];
                }
            }
        }

        public bool TryToEmbed(Module m) {
            for (int i = 0; i < 4; ++i) {
                for (int r = 0; r <= rows - m.rows; ++r) {
                    for (int c = 0; c <= cols - m.cols; ++c) {
                        if (IsAbleToEmbed(r, c, m)) {
                            Embed(r, c, m);
                            return true;
                        }
                    }
                }
                m = m.Rotate();
            }
            return false;
        }

        public Module Rotate() {
            Module clone = new Module(cols, rows);
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (isFilled[r, c]) {
                        clone.isFilled[c, rows-1-r] = true;
                    }
                }
            }
            return clone;
        }

        public int CountFilled() {
            int count = 0;
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (isFilled[r, c]) {
                        ++count;
                    }
                }
            }
            return count;
        }
    }

    class Program {
        static void Main(string[] args) {
            int[] tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (n, m, k) = (tokens[0], tokens[1], tokens[2]);

            Module laptop = new Module(n, m);

            for (int i = 0; i < k; ++i) {
                tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
                var (rows, cols) = (tokens[0], tokens[1]);
                int[][] rep = new int[rows][];
                for (int j = 0; j < rows; ++j) {
                    rep[j] = Console.ReadLine().Split().Select(int.Parse).ToArray();
                }
                Module sticker = new Module(rep);
                laptop.TryToEmbed(sticker);
            }

            Console.WriteLine(laptop.CountFilled());
        }
    }
}

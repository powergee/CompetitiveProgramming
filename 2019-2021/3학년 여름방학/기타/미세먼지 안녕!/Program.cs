using System;
using System.Collections.Generic;
using System.Linq;

namespace 미세먼지_안녕_ {
    class Map {
        private record Point(int Row, int Col);
        private List<Point> purifier;
        private int[,] dust;
        private int rows, cols;

        private static readonly Point[] DIRS = { 
            new Point(0, 1),
            new Point(0, -1),
            new Point(1, 0),
            new Point(-1, 0)
        };

        public Map(int[][] rawMap) {
            rows = rawMap.Length;
            cols = rawMap[0].Length;
            dust = new int[rows, cols];
            purifier = new List<Point>(2);

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    dust[r, c] = rawMap[r][c];
                    if (rawMap[r][c] == -1) {
                        purifier.Add(new Point(r, c));
                    }
                }
            }
        }

        public void Diffuse() {
            int[,] before = dust.Clone() as int[,];
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (dust[r, c] != -1) {
                        dust[r, c] = 0;
                    }
                }
            }

            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (before[r, c] == 0 || before[r, c] == -1) {
                        continue;
                    }

                    int count = 0;
                    int sub = before[r, c] / 5;

                    foreach (var dir in DIRS) {
                        int nr = dir.Row + r;
                        int nc = dir.Col + c;
                        if (0 <= nr && nr < rows && 0 <= nc && nc < cols && before[nr, nc] != -1) {
                            dust[nr, nc] += sub;
                            ++count;
                        }
                    }

                    dust[r, c] += before[r, c] - sub * count;
                }
            }
        }

        public void Purify() {
            dust[purifier[0].Row-1, 0] = 0;
            for (int r = purifier[0].Row-2; r >= 0; --r) {
                dust[r+1, 0] = dust[r, 0];
            }
            for (int c = 1; c < cols; ++c) {
                dust[0, c-1] = dust[0, c];
            }
            for (int r = 1; r <= purifier[0].Row; ++r) {
                dust[r-1, cols-1] = dust[r, cols-1];
            }
            for (int c = cols-2; c >= 1; --c) {
                dust[purifier[0].Row, c+1] = dust[purifier[0].Row, c];
            }
            dust[purifier[0].Row, 1] = 0;

            dust[purifier[1].Row+1, 0] = 0;
            for (int r = purifier[1].Row+2; r < rows; ++r) {
                dust[r-1, 0] = dust[r, 0];
            }
            for (int c = 1; c < cols; ++c) {
                dust[rows-1, c-1] = dust[rows-1, c];
            }
            for (int r = rows-2; r >= purifier[1].Row; --r) {
                dust[r+1, cols-1] = dust[r, cols-1];
            }
            for (int c = cols-2; c >= 1; --c) {
                dust[purifier[1].Row, c+1] = dust[purifier[1].Row, c];
            }
            dust[purifier[1].Row, 1] = 0;
        }

        public int SumDust() {
            int sum = 0;
            for (int r = 0; r < rows; ++r) {
                for (int c = 0; c < cols; ++c) {
                    if (dust[r, c] != -1) {
                        sum += dust[r, c];
                    }
                }
            }

            return sum;
        }
    }

    class Program {
        static void Main(string[] args) {
            var tokens = Console.ReadLine().Split().Select(int.Parse).ToArray();
            var (r, c, t) = (tokens[0], tokens[1], tokens[2]);
            
            int[][] rawMap = new int[r][];
            for (int i = 0; i < r; ++i) {
                rawMap[i] = Console.ReadLine().Split().Select(int.Parse).ToArray();
            }

            Map map = new Map(rawMap);

            while (t-- > 0) {
                map.Diffuse();
                map.Purify();
            }

            Console.WriteLine(map.SumDust());
        }
    }
}

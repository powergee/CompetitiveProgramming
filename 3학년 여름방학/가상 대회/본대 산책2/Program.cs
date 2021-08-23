﻿using System;

namespace 본대_산책2 {
    class Matrix {
        private long[,] nums;

        public int Rows => nums.GetLength(0);
        public int Columns => nums.GetLength(1);

        public ref long this[int r, int c] => ref nums[r, c];

        public Matrix(long[,] init) {
            nums = init.Clone() as long[,];
        }

        public Matrix(int rows, int cols) {
            nums = new long[rows, cols];
        }

        public static Matrix operator*(Matrix m1, Matrix m2) {
            if (m1.Columns != m2.Rows) {
                throw new ArgumentException();
            }
            Matrix result = new Matrix(m1.Rows, m2.Columns);
            for (int r = 0; r < result.Rows; ++r) {
                for (int c = 0; c < result.Columns; ++c) {
                    long sum = 0;
                    for (int i = 0; i < m1.Columns; ++i) {
                        sum += m1[r, i] * m2[i, c];
                        sum %= 1000000007;
                    }
                    result[r, c] = sum;
                }
            }
            return result;
        }

        public static Matrix CreateIdentity(int size) {
            Matrix result = new Matrix(size, size);
            for (int i = 0; i < size; ++i) {
                result[i, i] = 1;
            }
            return result;
        }
    }

    class Program {
        static Matrix Pow(Matrix matrix, int e) {
            if (e == 0) {
                return Matrix.CreateIdentity(matrix.Rows);
            } else if (e == 1) {
                return matrix;
            } else {
                Matrix half = Pow(matrix, e/2);
                Matrix result = half*half;
                if (e % 2 == 1) {
                    result *= matrix;
                }
                return result;
            }
        }

        static void Main(string[] args) {
            int d = int.Parse(Console.ReadLine());
            Matrix coeff = new Matrix(new long[8, 8] {
                { 0, 1, 1, 0, 0, 0, 0, 0 },
                { 1, 0, 1, 1, 0, 0, 0, 0 },
                { 1, 1, 0, 1, 1, 0, 0, 0 },
                { 0, 1, 1, 0, 1, 1, 0, 0 },
                { 0, 0, 1, 1, 0, 1, 1, 0 },
                { 0, 0, 0, 1, 1, 0, 0, 1 },
                { 0, 0, 0, 0, 1, 0, 0, 1 },
                { 0, 0, 0, 0, 0, 1, 1, 0 }
            });
            Matrix state = new Matrix(new long[8, 1] {
                { 1 },
                { 0 },
                { 0 },
                { 0 },
                { 0 },
                { 0 },
                { 0 },
                { 0 }
            });
            Matrix result = Pow(coeff, d) * state;
            Console.WriteLine(result[0, 0]);
        }
    }
}

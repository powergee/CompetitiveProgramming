using System;
using System.IO;
using System.Linq;

long n = long.Parse(Console.ReadLine());

Matrix basis = new Matrix(2);
basis[0, 0] = 0;
basis[1, 0] = basis[0, 1] = 1;
basis[1, 1] = 1;
Console.WriteLine(Pow(basis, n)[1, 0]);

Matrix Pow(Matrix matrix, long e) {
    if (e == 1) {
        return matrix;
    }

    Matrix sub = Pow(matrix, e/2);
    if (e % 2 == 0) {
        return sub * sub;
    } else {
        return sub * sub * matrix;
    }
}

class Matrix {
    private long[,] values;

    public int Rows { get; }

    public Matrix(int rows) {
        values = new long[rows, rows];
        Rows = rows;
    }

    public long this[int row, int col] {
        get {
            return values[row, col];
        }
        set {
            values[row, col] = value;
        }
    }
    
    public static Matrix operator*(Matrix m1, Matrix m2) {
        int rows = m1.values.GetLength(0);
        
        Matrix result = new Matrix(rows);
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < rows; ++c) {
                result[r, c] = 0;
                for (int i = 0; i < rows; ++i) {
                    result[r, c] += m1[r, i] * m2[i, c];
                    result[r, c] %= 1000000007;
                }
            }
        }

        return result;
    }
}
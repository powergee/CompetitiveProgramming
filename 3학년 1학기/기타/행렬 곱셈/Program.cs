using System;
using System.IO;
using System.Linq;

var tokens = Console.ReadLine().Split(' ');
int n = int.Parse(tokens[0]);
long e = long.Parse(tokens[1]);

Matrix matrix = new Matrix(n);
for (int i = 0; i < n; ++i) {
    var row = Console.ReadLine().Split(' ').Select(v => int.Parse(v)).ToArray();
    for (int j = 0; j < row.Length; ++j) {
        matrix[i, j] = row[j];
    }
}

Matrix result = Pow(matrix, e);
StreamWriter writer = new StreamWriter(Console.OpenStandardOutput());
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        writer.Write($"{result[i, j]} ");
    }
    writer.Write("\n");
}
writer.Close();

Matrix Pow(Matrix matrix, long e) {
    if (e == 1) {
        Matrix result = new Matrix(matrix.Rows);
        for (int i = 0; i < matrix.Rows; ++i) {
            for (int j = 0; j < matrix.Rows; ++j) {
                result[i, j] = matrix[i, j] % 1000;
            }
        }

        return result;
    }

    Matrix sub = Pow(matrix, e/2);
    if (e % 2 == 0) {
        return sub * sub;
    } else {
        return sub * sub * matrix;
    }
}

class Matrix {
    private int[,] values;

    public int Rows { get; }

    public Matrix(int rows) {
        values = new int[rows, rows];
        Rows = rows;
    }

    public int this[int row, int col] {
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
                    result[r, c] %= 1000;
                }
            }
        }

        return result;
    }
}
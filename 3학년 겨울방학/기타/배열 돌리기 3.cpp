#include <iostream>
#include <algorithm>
#include <vector>

class Matrix {
private:
    int h, w;
    std::vector<std::vector<int>> raw;

public:
    Matrix(int h, int w) : h(h), w(w) {
        raw.resize(h);
        for (auto& row : raw) {
            row.resize(w);
        }
    }

    int& at(int r, int c) {
        return raw[r][c];
    }

    int getHeight() {
        return h;
    }

    int getWidth() {
        return w;
    }

    void reverseVer() {
        std::reverse(raw.begin(), raw.end());
    }

    void reverseHor() {
        for (auto& row : raw) {
            std::reverse(row.begin(), row.end());
        }
    }

    void rotateRight() {
        Matrix result(w, h);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                result.at(j, h-1-i) = raw[i][j];
            }
        }
        *this = result;
    }

    void rotateLeft() {
        Matrix result(w, h);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                result.at(w-1-j, i) = raw[i][j];
            }
        }
        *this = result;
    }

    void rotateGroupsRight() {
        auto result = raw;
        for (int i = 0; i < h/2; ++i) {
            for (int j = 0; j < w/2; ++j) {
                result[i][j] = raw[i+h/2][j];
                result[i][j+w/2] = raw[i][j];
                result[i+h/2][j+w/2] = raw[i][j+w/2];
                result[i+h/2][j] = raw[i+h/2][j+w/2];
            }
        }
        raw = result;
    }

    void rotateGroupsLeft() {
        auto result = raw;
        for (int i = 0; i < h/2; ++i) {
            for (int j = 0; j < w/2; ++j) {
                result[i][j] = raw[i][j+w/2];
                result[i][j+w/2] = raw[i+h/2][j+w/2];
                result[i+h/2][j+w/2] = raw[i+h/2][j];
                result[i+h/2][j] = raw[i][j];
            }
        }
        raw = result;
    }
};

int main() {
    int n, m, r;
    scanf("%d %d %d", &n, &m, &r);

    Matrix mat(n, m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &mat.at(i, j));
        }
    }

    while (r--) {
        int op;
        switch (scanf("%d", &op), op)
        {
        case 1:
            mat.reverseVer();
            break;
        case 2:
            mat.reverseHor();
            break;
        case 3:
            mat.rotateRight();
            break;
        case 4:
            mat.rotateLeft();
            break;
        case 5:
            mat.rotateGroupsRight();
            break;
        case 6:
            mat.rotateGroupsLeft();
            break;
        }
    }

    for (int i = 0; i < mat.getHeight(); ++i) {
        for (int j = 0; j < mat.getWidth(); ++j) {
            printf("%d ", mat.at(i, j));
        }
        printf("\n");
    }

    return 0;
}
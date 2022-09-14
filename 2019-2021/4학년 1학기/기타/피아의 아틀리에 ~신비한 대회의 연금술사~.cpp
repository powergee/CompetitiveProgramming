#include <iostream>
#include <vector>
#include <functional>
#include <tuple>
#include <map>

template <size_t Dim, typename T>
struct TensorTemp {
    typedef std::vector<typename TensorTemp<Dim-1, T>::type> type;
};

template<typename T>
struct TensorTemp<1, T>  {
    typedef T type;
};

template <size_t Dim, typename T>
using Tensor = std::vector<typename TensorTemp<Dim, T>::type>;

template<typename T, typename FirstDim, typename... RestDims>
Tensor<sizeof...(RestDims)+1, T> createTensor(T init, FirstDim firstDim, RestDims... restDims) {
    constexpr size_t DimCount = sizeof...(restDims)+1;
    if constexpr (DimCount > 1) {
        return Tensor<DimCount, T>(firstDim, createTensor<T>(init, restDims...));
    } else {
        return Tensor<DimCount, T>(firstDim, init);
    }
}

struct Cell {
    int quality;
    char color;

    Cell() {
        quality = 0;
        color = 'W';
    }
};

class Matrix {
private:
    int h, w;
    std::vector<std::vector<Cell>> raw;

public:
    Matrix(int h, int w) : h(h), w(w) {
        raw.resize(h);
        for (auto& row : raw) {
            row.resize(w);
        }
    }

    Cell& at(int r, int c) {
        return raw[r][c];
    }

    int getHeight() {
        return h;
    }

    int getWidth() {
        return w;
    }

    Matrix rotateLeft() {
        Matrix result(w, h);
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                result.at(w-1-j, i) = raw[i][j];
            }
        }
        return result;
    }

    void apply(int r, int c, Matrix add) {
        for (int i = 0; i < add.getHeight(); ++i) {
            for (int j = 0; j < add.getWidth(); ++j) {
                at(r+i, c+j).quality = std::max(0, std::min(9, at(r+i, c+j).quality + add.at(i, j).quality));
                if (add.at(i, j).color != 'W') {
                    at(r+i, c+j).color = add.at(i, j).color;
                }
            }
        }
    }

    int getScore() {
        static const std::map<char, int> MULT = {
            { 'R', 7 },
            { 'B', 5 },
            { 'G', 3 },
            { 'Y', 2 },
            { 'W', 0 },
        };

        int result = 0;
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                result += MULT.at(at(i, j).color) * at(i, j).quality;
            }
        }
        return result;
    }
};

void iteratePerm(int n, int k, std::function<void(const std::vector<int>&)> callback) {
    std::vector<bool> inSelected(n+1, false);
    std::vector<int> selected;
    selected.reserve(k);
    std::function<void()> searchCases = [&]() {
        if (selected.size() == k) {
            callback(selected);
        } else {
            for (int i = 0; i < n; ++i) {
                if (!inSelected[i]) {
                    selected.push_back(i);
                    inSelected[i] = true;
                    searchCases();
                    selected.pop_back();
                    inSelected[i] = false;
                }
            }
        }
    };
    searchCases();
}

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Matrix> ingre(n, Matrix(4, 4));
    for (int i = 0; i < n; ++i) {
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                scanf("%d", &ingre[i].at(r, c).quality);
            }
        }
        for (int r = 0; r < 4; ++r) {
            for (int c = 0; c < 4; ++c) {
                char buffer[2];
                scanf("%s", buffer);
                ingre[i].at(r, c).color = buffer[0];
            }
        }
    }

    std::vector<std::tuple<int, int, int>> SINGLE;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 4; ++k) {
                SINGLE.emplace_back(i, j, k);
            }
        }
    }

    auto rotated = createTensor(Matrix(4, 4), n, 4);
    for (int i = 0; i < n; ++i) {
        rotated[i][0] = ingre[i];
        for (int k = 1; k < 4; ++k) {
            rotated[i][k] = rotated[i][k-1].rotateLeft();
        }
    }

    int answer = 0;
    iteratePerm(n, 3, [&](const std::vector<int>& sel) {
        for (auto [r1, c1, k1] : SINGLE) {
            for (auto [r2, c2, k2] : SINGLE) {
                for (auto [r3, c3, k3] : SINGLE) {
                    Matrix result(5, 5);
                    result.apply(r1, c1, rotated[sel[0]][k1]);
                    result.apply(r2, c2, rotated[sel[1]][k2]);
                    result.apply(r3, c3, rotated[sel[2]][k3]);
                    answer = std::max(answer, result.getScore());
                }
            }
        }
    });

    printf("%d", answer);

    return 0;
}
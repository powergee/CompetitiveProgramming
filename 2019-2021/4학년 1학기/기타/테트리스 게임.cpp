#include <iostream>
#include <vector>

using Map = std::vector<std::vector<int>>;

const Map T1 = {
    { 1, 1, 1, 1 }
};
const Map T2 = {
    { 1, 1, 0 },
    { 0, 1, 1 }
};
const Map T3 = {
    { 1, 1, 1 },
    { 0, 0, 1 }
};
const Map T4 = {
    { 1, 1, 1 },
    { 0, 1, 0 }
};
const Map T5 = {
    { 1, 1 },
    { 1, 1 }
};

Map rotateRight(const Map& m) {
    int r = m.size();
    int c = m[0].size();
    Map result(c, std::vector<int>(r));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            result[j][r-i-1] = m[i][j];
        }
    }
    return result;
}

int getProduct(const Map& board, const Map& block, int rOffset, int cOffset) {
    int result = 0;
    for (int i = 0; i < block.size(); ++i) {
        for (int j = 0; j < block[i].size(); ++j) {
            result += board[i+rOffset][j+cOffset] * block[i][j];
        }
    }
    return result;
}

int getMaxProduct(const Map& board, const Map& block) {
    int max = INT32_MIN;
    for (int i = 0; i <= board.size()-block.size(); ++i) {
        for (int j = 0; j <= board[0].size()-block[0].size(); ++j) {
            max = std::max(max, getProduct(board, block, i, j));
        }
    }
    return max;
}

int main() {
    int n, T = 1;
    while (scanf("%d", &n), n) {
        Map board(n, std::vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                scanf("%d", &board[i][j]);
            }
        }
        std::vector<Map> blocks = {
            T1, T2, T3, T4, T5
        };
        int result = INT32_MIN;
        for (int i = 0; i < blocks.size(); ++i) {
            for (int j = 0; j < 4; ++j) {
                result = std::max(result, getMaxProduct(board, blocks[i]));
                blocks[i] = rotateRight(blocks[i]);
            }
        }
        printf("%d. %d\n", T++, result);
    }

    return 0;
}
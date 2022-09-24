#include <iostream>
#include <vector>
#include <queue>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::vector<std::string> map(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> map[i];
    }

    auto isValid = [&](int r, int c) {
        return 0 <= r && r < n && 0 <= c && c < m;
    };

    auto getLength = [&](int rd, int cd) {
        std::queue<std::pair<int, int>> q;
        std::vector<std::vector<int>> length(n, std::vector<int>(m, -1));
        
        if (rd == -1) {
            for (int j = 0; j < m; ++j) {
                length[n-1][j] = (map[n-1][j] == '1');
                if (isValid(n-1+rd, j+cd)) {
                    q.emplace(n-1+rd, j+cd);
                }
            }
        }
        if (rd == 1) {
            for (int j = 0; j < m; ++j) {
                length[0][j] = (map[0][j] == '1');
                if (isValid(rd, j+cd)) {
                    q.emplace(rd, j+cd);
                }
            }
        }
        if (cd == -1) {
            for (int i = 0; i < n; ++i) {
                length[i][m-1] = (map[i][m-1] == '1');
                if (isValid(i+rd, m-1+cd)) {
                    q.emplace(i+rd, m-1+cd);
                }
            }
        }
        if (cd == 1) {
            for (int i = 0; i < n; ++i) {
                length[i][0] = (map[i][0] == '1');
                if (isValid(i+rd, cd)) {
                    q.emplace(i+rd, cd);
                }
            }
        }

        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            if (length[r][c] != -1) {
                continue;
            }

            length[r][c] = (map[r][c] == '1' ? length[r-rd][c-cd]+1 : 0);
            if (isValid(r+rd, c+cd)) {
                q.emplace(r+rd, c+cd);
            }
        }

        return length;
    };

    auto leftDown = getLength(-1, 1);
    auto rightDown = getLength(1, 1);
    auto leftUp = getLength(-1, -1);
    auto rightUp = getLength(1, -1);

    auto A = leftDown, V = leftUp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            A[i][j] = std::min(A[i][j], rightDown[i][j]);
            V[i][j] = std::min(V[i][j], rightUp[i][j]);
        }
    }

    

    return 0;
}
#include <iostream>
#include <vector>

int main() {
    int h, w;
    scanf("%d %d", &h, &w);
    std::vector<std::vector<int>> matrix(w, std::vector<int>(h));
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            scanf("%d", &matrix[j][i]);
        }
    }
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int w, h;
    scanf("%d %d", &w, &h);

    int q;
    scanf("%d", &q);

    std::vector<int> row, col;
    row.push_back(0);
    row.push_back(h);
    col.push_back(0);
    col.push_back(w);
    while (q--) {
        int kind, index;
        scanf("%d %d", &kind, &index);

        if (kind == 0) {
            row.push_back(index);
        } else {
            col.push_back(index);
        }
    }

    std::sort(row.begin(), row.end());
    std::sort(col.begin(), col.end());

    int answer = -1;
    for (int i = 0; i < (int)row.size()-1; ++i) {
        for (int j = 0; j < (int)col.size()-1; ++j) {
            answer = std::max(answer, (row[i+1]-row[i])*(col[j+1]-col[j]));
        }
    }

    printf("%d", answer);

    return 0;
}
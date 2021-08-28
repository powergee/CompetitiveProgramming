#include <vector>
#include <algorithm>
#include <iostream>

struct Table {
    int x1, y1, x2, y2;

    Table(int x1, int y1, int x2, int y2) {
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
};

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int w, h;
        scanf("%d %d", &w, &h);
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        
        int newW, newH;
        scanf("%d %d", &newW, &newH);
        
        std::vector<int> answers;
        int dist = std::max(newW-x1, 0);
        if (x2+(newW-x1) <= w) {
            answers.push_back(dist);
        }

        dist = std::max(newH-y1, 0);
        if (y2+(newH-y1) <= h) {
            answers.push_back(dist);
        }

        dist = std::max(y2-h+newH, 0);
        if (y1-(y2-h+newH) >= 0) {
            answers.push_back(dist);
        }

        dist = std::max(x2-w+newW, 0);
        if (x1-(x2-w+newW) >= 0) {
            answers.push_back(dist);
        }

        if (answers.empty()) {
            printf("-1\n");
        } else {
            printf("%d\n", *std::min_element(answers.begin(), answers.end()));
        }
    }

    return 0;
}
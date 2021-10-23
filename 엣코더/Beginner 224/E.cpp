#include <iostream>
#include <algorithm>
#include <vector>

typedef long long Long;

struct Point {
    int r, c, a, i;

    Point() {}
    Point(int r, int c, int a, int i) {
        this->r = r;
        this->c = c;
        this->a = a;
        this->i = i;
    }
};

bool comparePoints(const Point* p1, const Point* p2) {
    return p1->a < p2->a;
}

int main() {
    int h, w, n;
    scanf("%d %d %d", &h, &w, &n);

    std::vector<Point*> row[h+1];
    std::vector<Point*> col[w+1];
    std::vector<Point> points(n);

    for (int i = 0; i < n; ++i) {
        int r, c, a;
        scanf("%d %d %d", &r, &c, &a);
        points[i] = { r, c, a, i };
        row[r].push_back(&points[i]);
        col[c].push_back(&points[i]);
    }

    std::vector<Long> countDP(n, -1);
    std::vector<std::vector<Long>> rowSumDP(h+1);
    std::vector<std::vector<Long>> colSumDP(w+1);

    for (int r = 1; r <= h; ++r) {
        std::sort(row[r].begin(), row[r].end(), comparePoints);
        rowSumDP[r].resize(row[r].size(), -1);
    }
    for (int c = 1; c <= w; ++c) {
        std::sort(col[c].begin(), col[c].end(), comparePoints);
        colSumDP[c].resize(col[c].size(), -1);
    }

    std::function<Long(int)> countTimes;
    std::function<Long(int, int)> sumRow;
    std::function<Long(int, int)> sumCol;

    countTimes = [&](int start) -> Long {
        Long& result = countDP[start];
        if (result != -1) {
            return result;
        }

        result = 0;
        auto& curr = points[start];
        Point pivot = Point(0, 0, curr.a, 0);
        auto rowNext = std::upper_bound(row[curr.r].begin(), row[curr.r].end(), &pivot, comparePoints);
        auto colNext = std::upper_bound(col[curr.c].begin(), col[curr.c].end(), &pivot, comparePoints);

        if (rowNext != row[curr.r].end()) {
            result = std::max(sumRow(curr.r, rowNext - row[curr.r].begin()) + 1, result);
        }
        if (colNext != col[curr.c].end()) {
            result = std::max(sumCol(curr.c, colNext - col[curr.c].begin()) + 1, result);
        }
        return result;
    };

    sumRow = [&](int r, int start) -> Long {
        Long& result = rowSumDP[r][start];
        if (result != -1) {
            return result;
        }

        result = countTimes(row[r][start]->i);
        if (start+1 < row[r].size()) {
            result = std::max(sumRow(r, start+1), result);
        }
        return result;
    };

    sumCol = [&](int c, int start) -> Long {
        Long& result = colSumDP[c][start];
        if (result != -1) {
            return result;
        }

        result = countTimes(col[c][start]->i);
        if (start+1 < col[c].size()) {
            result = std::max(sumCol(c, start+1), result);
        }
        return result;
    };

    for (int i = 0; i < n; ++i) {
        printf("%lld\n", countTimes(i));
    }

    return 0;
}
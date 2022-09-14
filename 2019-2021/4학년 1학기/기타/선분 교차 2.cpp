#include <iostream>
#include <algorithm>

typedef long long Long;

struct Point {
    Long x, y;
    Point(Long x, Long y) : x(x), y(y) {}

    bool operator<(const Point& p) const {
        if (x != p.x) {
            return x < p.x;
        }
        return y < p.y;
    }

    bool operator<=(const Point& p) const {
        return (x == p.x && y == p.y) || *this < p;
    }
};

int calcCCW(Point p1, Point p2, Point p3) {
    Long op = p1.x*p2.y + p2.x*p3.y + p3.x*p1.y
            - p1.y*p2.x - p2.y*p3.x - p3.y*p1.x;
    if (op < 0) {
        return 1;
    } else if (op == 0) {
        return 0;
    } else {
        return -1;
    }
}

struct Line {
    Point p1, p2;
    Line(Long x1, Long y1, Long x2, Long y2) : p1(x1, y1), p2(x2, y2) {
        if (p2 < p1) {
            std::swap(p1, p2);
        }
    }

    bool isCrossedWith(const Line& other) const {
        int ab = calcCCW(p1, p2, other.p1) * calcCCW(p1, p2, other.p2);
        int cd = calcCCW(other.p1, other.p2, p1) * calcCCW(other.p1, other.p2, p2);

        if (ab == 0 && cd == 0) {
            return other.p1 <= p2 && p1 <= other.p2;
        }
        return ab <= 0 && cd <= 0;
    }
};

int main() {
    int x1, y1, x2, y2, x3, y3, x4, y4;
    std::cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;

    Line l1(x1, y1, x2, y2);
    Line l2(x3, y3, x4, y4);
    printf(l1.isCrossedWith(l2) ? "1" : "0");

    return 0;
}
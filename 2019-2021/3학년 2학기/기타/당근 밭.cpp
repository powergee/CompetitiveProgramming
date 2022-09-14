#include <iostream>

typedef long long Long;

Long countInner(Long r, Long end) {
    Long y = r, total = 0;
    for (Long x = 1; x <= end; ++x) {
        while (r*r - x*x < y*y) {
            --y;
        }
        total += y;
    }
    return total;
}

Long countInner(Long r) {
    return countInner(r, r);
}

int main() {
    Long w, h, r;
    std::cin >> w >> h >> r;
    if (w > h) {
        std::swap(w, h);
    }

    Long answer = 0;
    if (r <= w) {
        answer = 2*r + 3*countInner(r);
    } else if (r <= h) {
        answer = 3*r - w + 3*countInner(r) + countInner(r-w);
    } else if (r <= w+h) {
        answer = 4*r - w - h + 3*countInner(r) + countInner(r-w) + countInner(r-h);
    } else {
        answer = 4*r - w - h + 3*countInner(r) + (countInner(r-w)-countInner(r-w, r-w-h));
        Long y = r;
        for (Long x = 1; x <= r-h; ++x) {
            while ((r-h)*(r-h) - x*x < (y-h)*(y-h) && (r-w)*(r-w) - (x-w)*(x-w) < y*y) {
                --y;
            }
            answer += y - (x <= w ? h : 0);
        }
    }
    std::cout << answer;

    return 0;
}
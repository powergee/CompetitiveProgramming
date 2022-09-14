#include <iostream>
#include <algorithm>

typedef long long Long;

inline bool getDir(int dirs, int index) {
    return (dirs & (1<<index)) > 0;
}

Long countCollisions(int n, int t, int pos[], int dirs) {
    Long result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = i+1; j < n; ++j) {
            if (getDir(dirs, i) && !getDir(dirs, j) && pos[j]-pos[i] <= 2*t) {
                ++result;
            }
        }
    }
    return result;
}

int main() {
    int n, pos[12], t;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", pos+i);
    }
    std::sort(pos, pos+n);
    scanf("%d", &t);

    Long sum = 0;
    for (int dirs = 0; dirs < (1<<n); ++dirs) {
        sum += countCollisions(n, t, pos, dirs);
    }

    printf("%.9lf", (double)sum / (1<<n));
    return 0;
}
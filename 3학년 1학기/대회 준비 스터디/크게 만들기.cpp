#include <iostream>
#include <queue>
#include <algorithm>

struct Digit {
    int value, index;

    Digit(int val, int idx) {
        value = val;
        index = idx;
    }

    bool operator<(const Digit& d) const {
        if (value == d.value) {
            return index > d.index;
        }
        return value < d.value;
    }
};

char str[500001];

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    scanf("%s", str);
    int pushed = 0;

    std::priority_queue<Digit> window;
    int idxMin = 0;
    
    for (int i = 0; i < n-k; ++i) {
        while (pushed < std::min(k+1+i, n)) {
            window.emplace((int)(str[pushed]-'0'), pushed);
            ++pushed;
        }

        Digit max = window.top();
        window.pop();
        while (max.index < idxMin) {
            max = window.top();
            window.pop();
        }

        idxMin = max.index;
        printf("%d", max.value);
    }

    return 0;
}
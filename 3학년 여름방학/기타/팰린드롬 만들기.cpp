#include <iostream>
#include <cstring>

char line[1001];

bool isPalin(int left, int right) {
    if (right <= left) {
        return true;
    }
    if (line[left] != line[right]) {
        return false;
    }
    return isPalin(left+1, right-1);
}

int main() {
    scanf("%s", line);
    int n = strlen(line);
    int minL = __INT32_MAX__;
    for (int l = n-1; l >= 0; --l) {
        if (isPalin(l, n-1)) {
            minL = std::min(minL, l);
        }
    }
    printf("%d", n+minL);

    return 0;
}
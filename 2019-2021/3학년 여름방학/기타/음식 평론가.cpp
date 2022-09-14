#include <iostream>
#include <algorithm>
#include <numeric>

int main() {
    int n, m;
    int needLength, initLength;
    scanf("%d %d", &n, &m);

    std::pair<int, int> perMan(n, m);
    int gcd = std::gcd(perMan.first, perMan.second);
    perMan.first /= gcd;
    perMan.second /= gcd;

    needLength = perMan.first;
    initLength = perMan.second;

    int spare = 0;
    int answer = 0;
    for (int i = 0; i < n; ++i) {
        int currLength = initLength;
        while (currLength >= needLength-spare) {
            currLength -= needLength-spare;
            spare = 0;
            if (currLength > 0) {
                ++answer;
            }
        }
        spare += currLength;
    }

    printf("%d", answer);

    return 0;
}
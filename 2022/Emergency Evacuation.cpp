#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int r, s, p;
    std::cin >> r >> s >> p;
    
    std::vector<int> timeTable(r*s*2+10, 0);
    while (p--) {
        int i, j;
        std::cin >> i >> j;
        int optimal = (j <= s ? (s+1-j) : (j-s)) + (r-i+1);
        timeTable[optimal]++;
    }

    for (int i = 0; i+1 < timeTable.size(); ++i) {
        if (timeTable[i] >= 2) {
            timeTable[i+1] += timeTable[i]-1;
            timeTable[i] = 1;
        }
    }

    std::cout << timeTable.rend() - std::find_if(timeTable.rbegin(), timeTable.rend(), [](int v) { return v != 0; }) - 1 << "\n";

    return 0;
}
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

int main() {
    int n;
    scanf("%d", &n);

    std::vector<int> cands(n-1);
    std::iota(cands.begin(), cands.end(), 1);

    for (int round = 1; cands.size() > 1; ++round) {
        int mid = (int(cands.size())-1)/2;
        int c;
        for (c = 1; c < n && (cands[mid]+c)/n == (cands[mid+1]+c)/n; ++c);

        printf("+ %d\n", c);
        fflush(stdout);
        int res;
        scanf("%d", &res);
        
        if (res == (cands[mid]+c)/n) {
            cands = std::vector<int>(cands.begin(), cands.begin()+mid+1);
        } else {
            cands = std::vector<int>(cands.begin()+mid+1, cands.end());
        }
        std::transform(cands.begin(), cands.end(), cands.begin(), [&c](int x) { return x+c; });
    }

    printf("! %d\n", cands.front());
    
    return 0;
}
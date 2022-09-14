#include <iostream>
#include <string>
#include <vector>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string line;
    std::cin >> line;
    
    int n = line.size();
    std::vector<int> sum(n);
    sum[0] = (line[0] == '(' ? 1 : -1);
    for (int i = 1; i < n; ++i) {
        sum[i] = sum[i-1] + (line[i] == '(' ? 1 : -1);
    }

    std::vector<int> min = sum;
    for (int i = n-2; i >= 0; --i) {
        min[i] = std::min(min[i], min[i+1]);
    }

    int count = 0;
    if (line.front() == ')') {
        count = 1;
    } else {
        for (int i = 0; i < n; ++i) {
            int curr = (line[i] == '(' ? 1 : -1);
            if (sum[n-1] - curr == 0 && min[i] - curr == 0) {
                ++count;
            }
            if (sum[i] < 0) {
                break;
            }
        }
    }

    printf("%d", count);

    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>

struct LCG {
    int x, a, b, c;
    bool* appeared;
    std::vector<std::pair<int, int>> nums;

    LCG(int x, int a, int b, int c) {
        this->x = x;
        this->a = a;
        this->b = b;
        this->c = c;

        appeared = new bool[c];
        std::fill(appeared, appeared+c, false);
        appeared[x] = true;
        nums.emplace_back(x, 0);
        
        while (true) {
            int newVal = (a * nums.back().first + b) % c;
            if (appeared[newVal]) {
                break;
            } else {
                appeared[newVal] = true;
                nums.emplace_back(newVal, (int)nums.size());
            }
        }

        std::sort(nums.begin(), nums.end());
    }
};

int n, k;
std::vector<LCG*> lcgs;

int main() {
    scanf("%d %d", &n, &k);

    for (int i = 0; i < n; ++i) {
        int x, a, b, c;
        scanf("%d %d %d %d", &x, &a, &b, &c);
        lcgs.push_back(new LCG(x, a, b, c));
    }

    int sum = 0;
    std::vector<std::pair<int, int>> answer;
    for (int i = 0; i < n; ++i) {
        answer.push_back(lcgs[i]->nums.back());
        sum += lcgs[i]->nums.back().first;
    }

    bool success = true;
    if (sum % k == 0) {
        std::pair<std::pair<int, int>, int> minRepair = std::make_pair(std::make_pair(INT32_MAX, -1), -1);
        int minDiff = INT32_MAX;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < lcgs[i]->nums.size(); ++j) {
                int diff = lcgs[i]->nums.back().first - lcgs[i]->nums[j].first;
                if (diff % k != 0 && diff < minDiff) {
                    minDiff = diff;
                    minRepair = std::make_pair(lcgs[i]->nums[j], i);
                }
            }
        }
        if (minDiff == INT32_MAX) {
            success = false;
        } else {
            sum -= minDiff;
            answer[minRepair.second] = minRepair.first;
        }
    }

    if (success) {
        printf("%d\n", sum);
        for (auto p : answer) {
            printf("%d ", p.second);
        }
    } else {
        printf("-1");
    }

    return 0;
}
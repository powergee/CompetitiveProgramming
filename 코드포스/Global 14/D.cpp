#include <iostream>
#include <map>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, l, r;
        scanf("%d %d %d", &n, &l, &r);
        int lCopy = l;
        int rCopy = r;

        std::map<int, int> left, right;
        int answer = 0;
        
        for (int i = 0; i < lCopy; ++i) {
            int val;
            scanf("%d", &val);
            left[val] += 1;
        }

        for (int i = 0; i < rCopy; ++i)  {
            int val;
            scanf("%d", &val);
            if (left.find(val) == left.end() || left[val] == 0) {
                right[val] += 1;
            } else {
                left[val] -= 1;
                l--;
                r--;
            }
        }

        for (auto& p : left) {
            while (p.second >= 2 && r < l) {
                p.second -= 2;
                l -= 2;
                answer += 1;
            }
        }

        for (auto& p : right) {
            while (p.second >= 2 && l < r) {
                p.second -= 2;
                r -= 2;
                answer += 1;
            }
        }

        int max = std::max(l, r);
        int min = std::min(l, r);
        answer += max;
        printf("%d\n", answer);
    }
    
    return 0;
}
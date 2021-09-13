#include <iostream>
#include <string>
#include <vector>
#define MOD 1000000007

typedef long long Long;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        int n;
        std::string str;
        std::cin >> n >> str;
        
        Long answer = 0;
        std::vector<bool> isStart(n, false);
        std::vector<bool> isEnd(n, false);
        int first = str.find_first_not_of('F');
        if (first != std::string::npos) {
            std::pair<int, int>* range = new std::pair<int, int>(first, first);
            for (int i = first+1; i < n; ++i) {
                if (str[i] == 'F') {
                    continue;
                } else if (str[range->first] == str[i]) {
                    range->second = i;
                } else {
                    isStart[range->first] = true;
                    isEnd[range->second] = true;
                    delete range;
                    range = new std::pair<int, int>(i, i);
                }
            }
            isStart[range->first] = true;
            isEnd[range->second] = true;
            delete range;

            int prevEnd = -1;
            Long sum = 0;
            for (int i = 0; i < n; ++i) {
                if (isStart[i]) {
                    sum += prevEnd+1;
                    sum %= MOD;
                }
                if (isEnd[i]) {
                    prevEnd = i;
                }
                answer += sum;
                answer %= MOD;
            }
        }

        printf("Case #%d: %lld\n", t, answer);
    }
    
    return 0;
}
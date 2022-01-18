#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    while (T--) {
        int n, k;
        std::cin >> n >> k;
        std::string str;
        std::cin >> str;

        std::vector<int> count(26, 0);
        for (int i = 0; i < n; ++i) {
            count[str[i]-'a']++;
        }
        
        auto makeWord = [](int length, std::vector<int>& count) -> bool {
            std::sort(count.begin(), count.end());
            int currLength = 0;
            for (int i = 0; i < 26 && currLength < length; ++i) {
                int need = length - currLength;
                if (need <= count[i]) {
                    currLength = length;
                    count[i] -= need;
                } else if (length % 2 != 0 && currLength % 2 == 0) {
                    int use = count[i];
                    currLength += use;
                    count[i] -= use;
                } else {
                    int use = count[i] / 2 * 2;
                    currLength += use;
                    count[i] -= use;
                }
            }

            return currLength == length;
        };

        auto countWords = [&](int minLength) -> int {
            int result = 0;
            auto countCopy = count;
            while (makeWord(minLength, countCopy)) {
                ++result;
            }
            return result;
        };

        int left = 1, right = n/k;
        while (left+1 < right) {
            int mid = (left+right)/2;
            if (k <= countWords(mid)) {
                left = mid;
            } else {
                right = mid-1;
            }
        }

        int answer = 0;
        if (k <= countWords(right)) {
            answer = right;
        } else {
            answer = left;
        }

        std::cout << answer << "\n";
    }

    return 0;
}
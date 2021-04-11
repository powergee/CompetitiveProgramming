#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string reverseDir(std::string str) {
    std::string result;
    std::reverse(str.begin(), str.end());
    for (char ch : str) {
        result += std::to_string((ch-'1' + 2) % 4 + 1);
    }
    return result;
}

int main() {
    int n;
    scanf("%d", &n);

    std::string standard;
    for (int i = 0; i < n; ++i) {
        int val;
        scanf("%d", &val);
        standard += std::to_string(val);
    }

    int q;
    std::vector<std::string> result;
    scanf("%d", &q);
    for (int i = 0; i < q; ++i) {
        std::string test;
        for (int i = 0; i < n; ++i) {
            int val;
            scanf("%d", &val);
            test += std::to_string(val);
        }
        std::string rev = reverseDir(test);

        bool isSame = test == standard || rev == standard;
        for (int i = 0; i < n && !isSame; ++i) {
            if (test.substr(i) + test.substr(0, i) == standard) {
                isSame = true;
            }
        }
        for (int i = 0; i < n && !isSame; ++i) {
            if (rev.substr(i) + rev.substr(0, i) == standard) {
                isSame = true;
            }
        }

        if (isSame) {
            result.push_back(test);
        }
    }

    printf("%d\n", (int)result.size());

    for (int i = 0; i < result.size(); ++i) {
        for (char ch : result[i]) {
            printf("%c ", ch);
        }
        printf("\n");
    }

    return 0;
}
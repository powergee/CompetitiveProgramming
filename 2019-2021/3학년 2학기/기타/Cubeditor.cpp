#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int> getFail(std::string& str) {
    std::vector<int> fail(str.size(), 0);
    for (int i = 1, j = 0; i < (int)str.size(); ++i) {
        while (j > 0 && str[i] != str[j])
            j = fail[j-1];
        if (str[i] == str[j])
            fail[i] = ++j;
    }

    return fail;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    std::string str;
    std::cin >> str;

    int answer = 0;
    for (int i = 0; i < str.size(); ++i) {
        std::string sub = str.substr(i);
        std::vector<int> fail = getFail(sub);
        answer = std::max(answer, *std::max_element(fail.begin(), fail.end()));
    }

    printf("%d", answer);
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

typedef long long Long;

int findBack(std::string line, std::string back) {
    auto found = line.find_last_of(back[1]);
    if (found == std::string::npos || found == 0) {
        return INT32_MAX;
    }
    found = line.find_last_of(back[0], found-1);
    if (found == std::string::npos) {
        return INT32_MAX;
    }
    return int(line.size()) - (int(found) + 2);
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        Long n;
        scanf("%lld", &n);

        std::string line = std::to_string(n);
        std::vector<int> answers = {
            findBack(line, "25"),
            findBack(line, "50"),
            findBack(line, "75"),
            findBack(line, "00")
        };

        printf("%d\n", *std::min_element(answers.begin(), answers.end()));
    }

    return 0;
}
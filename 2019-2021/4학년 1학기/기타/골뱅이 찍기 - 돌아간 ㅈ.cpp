#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> TEMPLATE = {
    "@   @",
    "@  @",
    "@@@",
    "@  @",
    "@   @"
};

int main() {
    int n;
    std::cin >> n;

    std::vector<std::string> answer;
    answer.reserve(5*n);
    for (int i = 0; i < 5; ++i) {
        answer.push_back("");
        for (int j = 0; j < TEMPLATE[i].size(); ++j) {
            answer.back() += std::string(n, TEMPLATE[i][j]);
        }
        for (int i = 1; i < n; ++i) {
            answer.push_back(answer.back());
        }
    }

    for (std::string line : answer) {
        std::cout << line << "\n";
    }

    return 0;
}
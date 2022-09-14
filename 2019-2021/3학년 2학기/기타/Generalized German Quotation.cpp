#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string line;
    std::cin >> line;

    std::vector<int> rep(line.size()/2);
    std::vector<int> stack;
    std::string answer;
    for (int i = 0; i < line.size(); i += 2) {
        rep[i/2] = line[i] == '<' ? 1 : -1;
    }

    for (int r : rep) {
        if (!stack.empty() && stack.back() == r) {
            stack.pop_back();
            answer += ']';
        } else {
            stack.push_back(-r);
            answer += '[';
        }
    }

    if (stack.empty()) {
        std::cout << answer;
    } else {
        std::cout << "Keine Loesung";
    }

    return 0;
}
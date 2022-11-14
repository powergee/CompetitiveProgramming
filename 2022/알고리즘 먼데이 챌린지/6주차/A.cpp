#include <iostream>
#include <string>

int main() {
    for (int t = 0; t < 5; ++t) {
        std::string input;
        std::cin >> input;
        int answer = 0;
        for (int i = 0; i < input.size(); i += 2) {
            answer += input[i]-'0';
            answer %= 10;
        }
        for (int i = 1; i < input.size(); i += 2) {
            if (input[i] != '0') {
                answer *= input[i]-'0';
                answer %= 10;
            }
        }
        std::cout << answer % 10 << "\n";
    }

    return 0;
}
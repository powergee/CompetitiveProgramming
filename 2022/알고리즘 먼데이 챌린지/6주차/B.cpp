#include <iostream>
#include <string>

int main() {
    int n;
    std::cin >> n;
    std::string input;
    std::cin >> input;

    std::string answer;
    for (int i = 0; i < n; i += 2) {
        int k = input[i+1]-'0';
        answer += char('a' + (((input[i]-'a') + k*k) % 26));
    }
    std::cout << answer;

    return 0;
}
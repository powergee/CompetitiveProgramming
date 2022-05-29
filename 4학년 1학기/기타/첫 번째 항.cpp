#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string curr;
    int T = 1;
    while ((std::cin >> curr), curr != "0") {
        while (true) {
            if (curr.size() % 2) {
                std::cout << "Test " << T << ": " << curr << "\n";
                break;
            } else {
                std::string prev;
                for (int i = 0; i < curr.size(); i += 2) {
                    int count = curr[i]-'0';
                    for (int j = 0; j < count; ++j) {
                        prev += curr[i+1];
                    }
                }
                if (prev == curr) {
                    std::cout << "Test " << T << ": " << curr << "\n";
                    break;
                }
                curr = prev;
            }
        }
        ++T;
    }

    return 0;
}
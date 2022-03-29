#include <iostream>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        std::string n;
        std::cin >> n;
        
        int sum = 0;
        for (int i = 0; i < n.size(); ++i) {
            sum += n[i] - '0';
        }
        int toInsert = ((sum / 9) + (sum % 9 ? 1 : 0))*9 - sum;

        std::cout << "Case #" << t << ": ";
        bool printed = false;
        for (int i = 0; i < n.size(); ++i) {
            if ((i > 0 || toInsert > 0) && toInsert < n[i]-'0' && !printed) {
                std::cout << toInsert;
                printed = true;
            }
            std::cout << n[i];
        }

        if (!printed) {
            std::cout << toInsert;
        }
        std::cout << "\n";
    }

    return 0;
}
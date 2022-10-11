#include <iostream>
#include <string>

int main() {
    int n;
    std::string origin;
    std::cin >> n >> origin;

    int answer = 0;
    for (int i = 0; i < n; ++i) {
        std::string v;
        std::cin >> v;
        for (int j = 0; v.size() >= origin.size() && j <= v.size()-origin.size(); ++j) {
            if (v.substr(j, origin.size()) == origin) {
                answer++;
                break;
            }
        }
    }

    std::cout << answer;

    return 0;
}
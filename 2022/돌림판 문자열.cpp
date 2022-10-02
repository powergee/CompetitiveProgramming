#include <iostream>
#include <vector>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    
    int n, m;
    std::string rolling, s;
    std::cin >> n >> rolling;
    std::cin >> m >> s;

    int answer = 0;
    for (int i = 0, pointing = n-1; i < s.size(); ++i) {
        if (rolling.find(s[i]) == rolling.npos) {
            std::cout << "-1";
            return 0;
        }

        do {
            pointing = (pointing+1) % n;
            ++answer;
        } while (rolling[pointing] != s[i]);
    }

    std::cout << answer;

    return 0;
}
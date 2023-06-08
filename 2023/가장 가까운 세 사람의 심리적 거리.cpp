#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

int dist(const std::string& s1, const std::string& s2) {
    int result = 0;
    for (std::size_t i = 0; i < s1.size(); ++i) {
        if (s1[i] != s2[i]) {
            result += 1;
        }
    }
    return result;
}

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::cin >> n;
        std::unordered_map<std::string, int> s;
        while (n--) {
            std::string mbti;
            std::cin >> mbti;
            s[mbti] += 1;
        }
        if (std::any_of(s.begin(), s.end(),
                        [](auto p1) { return p1.second >= 3; })) {
            std::cout << 0 << "\n";
        } else {
            std::vector<std::string> s_vec;
            s_vec.reserve(32);
            for (auto [mbti, cnt] : s) {
                for (int i = 0; i < cnt; ++i) {
                    s_vec.push_back(mbti);
                }
            }
            int answer = 1000;
            for (std::size_t i = 0; i < s_vec.size(); ++i) {
                for (std::size_t j = i + 1; j < s_vec.size(); ++j) {
                    for (std::size_t k = j + 1; k < s_vec.size(); ++k) {
                        int curr_dist = dist(s_vec[i], s_vec[j]) +
                                        dist(s_vec[j], s_vec[k]) +
                                        dist(s_vec[i], s_vec[k]);
                        answer = std::min(answer, curr_dist);
                    }
                }
            }
            std::cout << answer << "\n";
        }
    }

    return 0;
}
#include <iostream>
#include <algorithm>
#include <string>
#include <set>

struct State {
    short count[26];

    State() {
        std::fill(count, count+26, 0);
    }

    bool compare(const State& s, int pos) const {
        if (pos == 26) {
            return false;
        }
        if (count[pos] != s.count[pos]) {
            return count[pos] < s.count[pos];
        }
        return compare(s, pos+1);
    }

    bool operator<(const State& s) const {
        return compare(s, 0);
    }
};

std::set<State> appeared[1501];

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string w1, w2;
    std::cin >> w1 >> w2;

    for (int i = 0; i < w1.size(); ++i) {
        State mask;
        for (int j = i; j < w1.size(); ++j) {
            mask.count[w1[j]-'a']++;
            appeared[j-i+1].insert(mask);
        }
    }

    int answer = 0;
    for (int i = 0; i < w2.size(); ++i) {
        State mask;
        for (int j = i; j < w2.size(); ++j) {
            mask.count[w2[j]-'a']++;
            if (appeared[j-i+1].find(mask) != appeared[j-i+1].end()) {
                answer = std::max(answer, j-i+1);
            }
        }
    }
    
    std::cout << answer;
    return 0;
}
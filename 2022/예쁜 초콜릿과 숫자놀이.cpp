#include <iostream>
#include <functional>

typedef long long Long;
const Long MOD = 100000;

Long iterateSequences(int open, Long a, Long b, Long c) {
    std::vector<Long> seq;
    seq.reserve(2*open+1);
    seq.push_back(a);
    Long result = 0;
    std::function<void(int, int, int)> searchCases = [&](int start, int opened, int level) {
        if (seq.size() == 2*open+1) {
            result = std::max(result, seq.back());
            return;
        }
        if (level > 0) {
            seq.push_back((seq.back()*c) % MOD);
            searchCases(start+1, opened, level-1);
            seq.pop_back();
        }
        if (opened < open) {
            seq.push_back((seq.back()+b) % MOD);
            searchCases(start+1, opened+1, level+1);
            seq.pop_back();
        }
    };
    searchCases(0, 0, 0);
    return result;
}

int main() {
    Long n, a, b, c;
    std::cin >> n >> a >> b >> c;
    std::cout << iterateSequences(n, a, b, c);

    return 0;
}
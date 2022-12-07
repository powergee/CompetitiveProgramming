#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <functional>

using Long = unsigned long long;

const Long MAX = 1'000'000'000'000'000'000ULL;
const std::string NATO_PLAIN[26] = { "ALFA", "BRAVO", "CHARLIE", "DELTA", "ECHO", "FOXTROT", "GOLF", "HOTEL", "INDIA", "JULIETT", "KILO", "LIMA", "MIKE", "NOVEMBER", "OSCAR", "PAPA", "QUEBEC", "ROMEO", "SIERRA", "TANGO", "UNIFORM", "VICTOR", "WHISKEY", "XRAY", "YANKEE", "ZULU" };

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    std::string init;
    int q;
    std::cin >> init >> q;

    std::vector<std::vector<Long>> alphaLen(1, std::vector<Long>(26, 1));
    for (int e = 1; ; ++e) {
        alphaLen.emplace_back(26, 0);
        bool finished = true;
        for (int i = 0; i < 26; ++i) {
            for (char c : NATO_PLAIN[i]) {
                alphaLen[e][i] += alphaLen[e-1][c-'A'];
                alphaLen[e][i] = std::min(alphaLen[e][i], MAX);
            }
            if (alphaLen[e][i] < MAX) {
                finished = false;
            }
        }
        if (finished) {
            break;
        }
    }

    std::vector<std::vector<Long>> initLen(alphaLen.size(), std::vector<Long>(init.size(), 0));
    for (size_t e = 0; e < alphaLen.size(); ++e) {
        initLen[e][0] = alphaLen[e][init[0]-'A'];
        for (size_t i = 1; i < init.size(); ++i) {
            initLen[e][i] = initLen[e][i-1] + alphaLen[e][init[i]-'A'];
            initLen[e][i] = std::min(initLen[e][i], MAX);
        }
    }

    std::function<char(int, size_t, Long)> getCharAt = [&](int startAlpha, size_t transCount, Long pos) -> char {
        if (transCount == 0) {
            assert(pos == 0);
            return char(startAlpha + 'A');
        }
        Long prevLen = 0;
        for (size_t i = 0; i < NATO_PLAIN[startAlpha].size(); ++i) {
            auto segLen = alphaLen[transCount-1][NATO_PLAIN[startAlpha][i]-'A'];
            if (pos < prevLen + segLen) {
                return getCharAt(NATO_PLAIN[startAlpha][i]-'A', transCount-1, pos - prevLen);
            }
            prevLen += segLen;
        }
        std::cerr << startAlpha << " " << transCount << " " << pos << " " << prevLen << "\n";
        assert(false);
        return '\0';
    };

    size_t transCount = 0;
    while (q--) {
        int op;
        Long arg;
        std::cin >> op >> arg;
        
        if (op == 1) {
            transCount = std::min(100, int(transCount + arg));
        } else {
            Long pos = arg;

            if (transCount < alphaLen.size()) {
                int left = 0, right = init.size()-1;
                while (left < right) {
                    int mid = (left + right) / 2;
                    if (pos <= initLen[transCount][mid]) {
                        right = mid;
                    } else {
                        left = mid+1;
                    }
                }
                std::cout << getCharAt(
                    init[left]-'A',
                    transCount,
                    pos - 1 - (left == 0 ? 0 : initLen[transCount][left-1])
                );
            } else {
                std::cout << getCharAt(
                    init[0]-'A',
                    alphaLen.size()-1,
                    pos - 1
                );
            }
        }
    }

    return 0;
}
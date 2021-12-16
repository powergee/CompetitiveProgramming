#include <cstdio>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int T;
    std::cin >> T;

    while (T--) {
        std::string s, t;
        std::cin >> s >> t;

        if (s.find('a') == std::string::npos || s.find('b') == std::string::npos || s.find('c') == std::string::npos) {
            std::sort(s.begin(), s.end());
            std::cout << s << "\n";
        } else {
            std::map<char, char> chMap;
            std::map<char, char> chMapInv;

            std::string seq = "abc";
            do {
                if (seq != t) {
                    for (int i = 0; i < 3; ++i) {
                        chMap[seq[i]] = 'a'+i;
                        chMapInv['a'+i] = seq[i];
                    }
                    break;
                }
            } while (std::next_permutation(seq.begin(), seq.end()));

            for (int i = 0; i < s.size(); ++i) {
                if ('a' <= s[i] && s[i] <= 'c') {
                    s[i] = chMap[s[i]];
                }
            }
            std::sort(s.begin(), s.end());
            for (int i = 0; i < s.size(); ++i) {
                if ('a' <= s[i] && s[i] <= 'c') {
                    s[i] = chMapInv[s[i]];
                }
            }

            std::cout << s << "\n";
        }
    }

    return 0;
}

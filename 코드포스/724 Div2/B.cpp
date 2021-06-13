#include <iostream>
#include <string>
#include <algorithm>

int n;
std::string line;
bool single[26];
bool doub[26][26];
bool triple[26][26][26];

char findSingle() {
    std::fill(single, single+26, false);
    for (int i = 0; i < line.size(); ++i) {
        single[line[i]-'a'] = true;
    }
    for (int i = 0; i < 26; ++i) {
        if (!single[i]) {
            return i+'a';
        }
    }
    return 0;
}

std::string findDouble() {
    std::fill(&doub[0][0], &doub[0][0]+26*26, false);
    for (int i = 0; i < (int)line.size()-1; ++i) {
        doub[line[i]-'a'][line[i+1]-'a'] = true;
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            if (!doub[i][j]) {
                std::string result;
                result += i+'a';
                result += j+'a';
                return result;
            }
        }
    }
    return "";
}

std::string findTriple() {
    std::fill(&triple[0][0][0], &triple[0][0][0]+26*26*26, false);
    for (int i = 0; i < (int)line.size()-2; ++i) {
        triple[line[i]-'a'][line[i+1]-'a'][line[i+2]-'a'] = true;
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            for (int k = 0; k < 26; ++k) {
                if (!triple[i][j][k]) {
                    std::string result;
                    result += i+'a';
                    result += j+'a';
                    result += k+'a';
                    return result;
                }
            }
        }
    }
    return "";
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        std::cin >> n >> line;

        char s;
        if (s = findSingle()) {
            std::cout << s << "\n";
            continue;
        }

        std::string str;
        if ((str = findDouble()) != "") {
            std::cout << str << "\n";
            continue;
        }
        if ((str = findTriple()) != "") {
            std::cout << str << "\n";
            continue;
        }
    }

    return 0;
}
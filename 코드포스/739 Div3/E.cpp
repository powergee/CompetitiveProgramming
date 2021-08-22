#include <iostream>
#include <algorithm>
#include <string>

std::string t, seq;

bool isSame(int count1[], int count2[]) {
    for (int i = 0; i < 26; ++i) {
        if (count1[i] != count2[i]) {
            return false;
        }
    }
    return true;
}

bool validatePrefix(std::string s) {
    std::string result = "";
    for (int i = 0; i < seq.size(); ++i) {
        result += s;
        std::string newS = "";
        for (char c : s) {
            if (c != seq[i]) {
                newS += c;
            }
        }
        s = newS;
    }

    return result == t;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        std::cin >> t;

        int currCount[26] = {0, };
        seq = "";

        for (int i = (int)t.size()-1; i >= 0; --i) {
            currCount[t[i]-'a']++;
            if (currCount[t[i]-'a'] == 1) {
                seq += t[i];
            }
        }

        std::reverse(seq.begin(), seq.end());

        int tCount[26] = {0,}, pCount[26] = {0,};
        for (char tc : t) {
            tCount[tc-'a']++;
        }
        
        std::string s;
        bool valid = false;
        for (int i = 0; i < t.size(); ++i) {
            pCount[t[i]-'a']++;
            int estimated[26] = {0,};
            for (int j = 0; j < seq.size(); ++j) {
                estimated[seq[j]-'a'] = pCount[seq[j]-'a'] * (j+1);
            }
            
            if (isSame(tCount, estimated)) {
                // std::cout << "[in]";
                s = t.substr(0, i+1);
                valid = validatePrefix(s);
                break;
            }
        }

        if (valid) {
            std::cout << s << " " << seq << "\n";
        } else {
            std::cout << "-1\n";
        }
    }

    return 0;
}
#include <iostream>
#include <string>
#include <map>

int main() {
    std::cin.tie(nullptr)->sync_with_stdio(false);

    std::string s, t;
    std::cin >> s >> t;

    std::map<int, int> tIndex;
    for (int i = 0; i < t.size(); ++i) {
        tIndex[t[i]] = i;
    }

    std::map<int, int> built;
    for (int i = 0; i < s.size(); ++i) {
        if (tIndex.find(s[i]) == tIndex.end()) {
            continue;
        }
        int idx = tIndex[s[i]];
        if (idx == 0) {
            built[0]++;
        } else if (built[idx-1]) {
            built[idx-1]--;
            built[idx]++;
        }
    }
    printf("%d", built[int(t.size())-1]);

    return 0;
}
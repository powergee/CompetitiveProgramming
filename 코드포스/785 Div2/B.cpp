#include <iostream>
#include <cstring>
#include <vector>

char line[200001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", line);
        int n = strlen(line);
        
        bool yes = true;
        std::vector<char> temp;
        temp.reserve(n);
        for (char c1 = 'a'; c1 <= 'z'; ++c1) {
            for (char c2 = c1+1; c2 <= 'z'; ++c2) {
                for (int i = 0; i < n; ++i) {
                    if (c1 == line[i] || c2 == line[i]) {
                        temp.push_back(line[i]);
                    }
                }
                for (int i = 0; i+2 < temp.size(); ++i) {
                    if (temp[i] == temp[i+1] && temp[i] != temp[i+2]) {
                        yes = false;
                    }
                    if (temp[i+1] == temp[i+2] && temp[i] != temp[i+2]) {
                        yes = false;
                    }
                }
                temp.resize(0);
            }
        }

        printf(yes ? "YES\n" : "NO\n");
    }

    return 0;
}
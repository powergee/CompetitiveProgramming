#include <iostream>
#include <vector>

char getOpposite(char val) {
    if (val == '=') {
        return val;
    }
    return val == '+' ? '-' : '+';
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        char types[n+1];
        scanf("%s", types);

        std::vector<int> t1, t2;
        for (int i = 0; i < n; ++i) {
            if (types[i] == '2') {
                t2.push_back(i);
            } else {
                t1.push_back(i);
            }
        }

        bool yes = true;
        char result[n][n+1];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                result[i][j] = '\0';
            }
            result[i][i] = 'X';
            result[i][n] = '\0';
        }

        if (!t2.empty()) {
            if (t2.size() >= 3) {
                for (int i = 0; i < t2.size()-1; ++i) {
                    result[t2[i]][t2[i+1]] = '+';
                    for (int j = i+2; j < t2.size(); ++j) {
                        result[t2[i]][t2[j]] = '-';
                    }
                }
            } else {
                yes = false;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                if (result[i][j] == '\0') {
                    result[i][j] = '=';
                }
                
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                result[i][j] = getOpposite(result[j][i]);
            }
        }

        if (yes) {
            printf("YES\n");
            for (int i = 0; i < n; ++i) {
                printf("%s\n", result[i]);
            }
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
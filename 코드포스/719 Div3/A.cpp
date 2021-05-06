#include <iostream>
#include <cstring>
#include <algorithm>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        char str[51];
        bool done[26];
        bool yes = true;
        scanf("%s", str);

        std::fill(done, done+26, false);
        for (int i = 0; i < n; ++i) {
            int idx = str[i]-'A';
            if (!done[idx]) {
                done[idx] = true;
            } else if (i > 0 && str[i-1] != str[i]) {
                yes = false;
            }
        }

        if (yes) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}
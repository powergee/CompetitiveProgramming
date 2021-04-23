#include <iostream>
#include <vector>

char str[100001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        scanf("%s", str);
        
        bool yes = true;
        int count = 0;
        for (int i = 0; i < n; ++i) {
            if (str[i] == 'T') {
                ++count;
            } else {
                --count;
            }

            if (count < 0) {
                yes = false;
            }
        }

        if (count*3 != n) {
            yes = false;
        }

        count = 0;
        for (int i = n-1; i >= 0; --i) {
            if (str[i] == 'T') {
                ++count;
            } else {
                --count;
            }

            if (count < 0) {
                yes = false;
            }
        }

        if (count*3 != n) {
            yes = false;
        }

        if (yes) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}
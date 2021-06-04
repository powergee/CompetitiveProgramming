#include <iostream>
#include <algorithm>

char str[1001];
char temp[1001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        scanf("%s", str);

        while (m--) {
            bool updated = false;

            std::copy(str, str+n, temp);
            for (int i = 0; i < n; ++i) {
                if (str[i] == '0' && ((0 < i && str[i-1] == '1') ^ (i < n-1 && str[i+1] == '1'))) {
                    temp[i] = '1';
                    updated = true;
                }
            }
            std::copy(temp, temp+n, str);
            if (!updated) {
                break;
            }
        }
        printf("%s\n", str);
    }

    return 0;
}
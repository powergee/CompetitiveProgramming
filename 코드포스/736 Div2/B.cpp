#include <iostream>

char enemy[200001];
char mine[200001];
bool used[200001];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);
        scanf("%s", enemy);
        scanf("%s", mine);

        for (int i = 0; i < n; ++i) {
            used[i] = false;
        }

        int answer = 0;
        for (int i = 0; i < n; ++i) {
            if (mine[i] == '1') {
                if (i > 0 && enemy[i-1] == '1' && !used[i-1]) {
                    enemy[i-1] = '0';
                    used[i-1] = true;
                    answer++;
                } else if (enemy[i] == '0' && !used[i]) {
                    used[i] = true;
                    answer++;
                } else if (i < n-1 && enemy[i+1] == '1' && !used[i+1]) {
                    enemy[i+1] = '0';
                    used[i+1] = true;
                    answer++;
                }
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}
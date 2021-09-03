#include <iostream>
#include <cstring>
#include <vector>

char str[101];
int dist[26][26];

int main() {
    int T;
    scanf("%d", &T);

    for (int t = 1; t <= T; ++t) {
        scanf("%s", str);
        int n = std::strlen(str);

        for (int i = 0; i < 26; ++i) {
            for (int j = 0; j < 26; ++j) {
                dist[i][j] = INT32_MAX / 2;
            }
            dist[i][i] = 0;
        }

        int m;
        scanf("%d", &m);
        for (int i = 0; i < m; ++i) {
            char word[3];
            scanf("%s", word);
            dist[word[0]-'A'][word[1]-'A'] = 1;
        }

        for (int m = 0; m < 26; ++m) {
            for (int i = 0; i < 26; ++i) {
                for (int j = 0; j < 26; ++j) {
                    dist[i][j] = std::min(dist[i][j], dist[i][m] + dist[m][j]);
                }
            }
        }

        int answer = INT32_MAX;
        for (char pivot = 'A'; pivot <= 'Z'; ++pivot) {
            int count = 0;
            for (int i = 0; i < n; ++i) {
                if (dist[str[i]-'A'][pivot-'A'] == INT32_MAX / 2) {
                    count = INT32_MAX;
                    break;
                }
                count += dist[str[i]-'A'][pivot-'A'];
            }
            answer = std::min(answer, count);
        }
        
        printf("Case #%d: %d\n", t, (answer == INT32_MAX ? -1 : answer));
    }

    return 0;
}
#include <iostream>

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        long long answer = 0;
        int count[11][11] = {0};
        for (int i = 0; i < n; ++i) {
            char word[3];
            scanf("%s", word);
            for (char c = 'a'; c <= 'k'; ++c) {
                if (c != word[1]) {
                    answer += count[word[0]-'a'][c-'a'];
                }
            }
            for (char c = 'a'; c <= 'k'; ++c) {
                if (c != word[0]) {
                    answer += count[c-'a'][word[1]-'a'];
                }
            }
            count[word[0]-'a'][word[1]-'a']++;
        }

        printf("%lld\n", answer);
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    char str[n+1];
    scanf("%s", str);

    int currLength = 0;
    std::vector<int> sections;
    for (int i = 0; i < n; ++i) {
        if (str[i] == '0') {
            currLength++;
        } else {
            if (currLength) {
                sections.push_back(currLength);
            }
            currLength = 0;
        }
    }
    if (currLength) {
        sections.push_back(currLength);
    }

    std::sort(sections.begin(), sections.end(), std::greater<int>());
    int answer = 0;
    for (int i = 0; i < std::min(k, int(sections.size())); ++i) {
        answer += sections[i];
    }
    printf("%d\n", answer);

    return 0;
}
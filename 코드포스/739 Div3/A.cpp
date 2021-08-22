#include <iostream>
#include <vector>

int main() {
    std::vector<int> answers;
    for (int i = 1; answers.size() < 1000; ++i) {
        if (i % 3 != 0 && i % 10 != 3) {
            answers.push_back(i);
        }
    }

    int T;
    scanf("%d", &T);

    while (T--) {
        int k;
        scanf("%d", &k);
        printf("%d\n", answers[k-1]);
    }

    return 0;
}
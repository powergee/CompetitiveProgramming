#include <iostream>
#include <string>

int main() {
    int n;
    scanf("%d", &n);

    std::basic_string<int> seq;
    seq += 1;

    for (int i = 2; i <= n; ++i) {
        seq = seq + i + seq;
    }
    for (int v : seq) {
        printf("%d ", v);
    }

    return 0;
}
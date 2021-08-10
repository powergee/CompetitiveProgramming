#include <iostream>
#include <algorithm>

bool isPrime[246913];
int count[246913];

int main() {
    std::fill(isPrime, isPrime+246913, true);
    isPrime[0] = isPrime[1] = false;
    for (long long i = 2; i <= 246912; ++i) {
        if (isPrime[i]) {
            for (long long j = i*i; j <= 246912; j += i) {
                isPrime[j] = false;
            }
        }
    }
    
    count[0] = 0;
    for (int i = 1; i < 246913; ++i) {
        count[i] = count[i-1] + (isPrime[i] ? 1 : 0);
    }

    int n;
    while (scanf("%d", &n), n != 0) {
        printf("%d\n", count[2*n]-count[n]);
    }
    
    return 0;
}
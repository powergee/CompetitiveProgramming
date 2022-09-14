#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    bool isPrime[1000];
    std::fill(isPrime, isPrime+1000, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i*i < 1000; ++i) {
        if (isPrime[i]) {
            for (int j = i*i; j < 1000; j += i) {
                isPrime[j] = false;
            }
        }
    }

    std::vector<int> primes;
    for (int i = 0; i < 1000; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
    }

    std::vector<std::pair<int, int>> twoSum(2000, std::make_pair(-1, -1));
    for (int i = 0; i < primes.size(); ++i) {
        for (int j = i; j < primes.size(); ++j) {
            int sum = primes[i] + primes[j];
            twoSum[sum] = { primes[i], primes[j] };
        }
    }

    int T;
    scanf("%d", &T);

    while (T--) {
        int k;
        scanf("%d", &k);

        bool printed = false;
        for (int p : primes) {
            if (k <= p) {
                break;
            }
            int spare = k - p;
            if (twoSum[spare].first != -1) {
                int answer[] = {
                    twoSum[spare].first,
                    twoSum[spare].second,
                    p
                };
                std::sort(answer, answer+3);
                for (int i = 0; i < 3; ++i) {
                    printf("%d ", answer[i]);
                }
                printf("\n");
                printed = true;
                break;
            }
        }

        if (!printed) {
            printf("0\n");
        }
    }

    return 0;
}
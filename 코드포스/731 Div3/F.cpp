#include <iostream>
#include <algorithm>
#include <numeric>
#include <set>
#include <map>

int arr[200000];
std::set<int> totalPrimes;
std::set<int> primes[200000];

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%d", arr+i);
        }

        if (*std::max_element(arr, arr+n) == *std::min_element(arr, arr+n)) {
            printf("0\n");
            continue;
        }

        int globalGCD = arr[0];
        for (int i = 1; i < n; ++i) {
            globalGCD = std::gcd(globalGCD, arr[i]);
        }

        for (int i = 0; i < n; ++i) {
            arr[i] /= globalGCD;

            int div;
            int temp = arr[i];
            for (div = 2; div*div <= arr[i];) {
                if (temp % div == 0) {
                    temp /= div;
                    totalPrimes.insert(div);
                    primes[i].insert(div);
                } else {
                    ++div;
                }
            }
            if (temp > 1) {
                totalPrimes.insert(temp);
                primes[i].insert(temp);
            }
        }

        int maxLength = 0;
        for (int i = 0; i < n; ++i) {
            std::set<int> subtract;
            std::set_difference(primes[i].begin(), primes[i].end(),
                                primes[(i+1)%n].begin(), primes[(i+1)%n].end(),
                                std::inserter(subtract, subtract.end()));
            
            for (int p : subtract) {
                int length = 1;
                for (int j = (i == 0 ? n-1 : i-1); j != i; j = (j == 0 ? n-1 : j-1)) {
                    if (primes[j].find(p) == primes[j].end()) {
                        break;
                    } else {
                        ++length;
                    }
                }
                maxLength = std::max(maxLength, length);
            }
        }

        printf("%d\n", maxLength);

        for (int i = 0; i < n; ++i) {
            primes[i].clear();
        }
    }

    return 0;
}
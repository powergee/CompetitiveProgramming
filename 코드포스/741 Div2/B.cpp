#include <iostream>
#include <string>
#include <map>

bool isSubsequence(std::string main, std::string sub) {
    int start = 0;
    for (int i = 0; i < sub.size(); ++i) {
        int found = main.find_first_of(sub[i], start);
        if (found == std::string::npos) {
            return false;
        }
        start = found+1;
    }
    return true;
}

bool isPrime[1000];

int main() {
    std::fill(isPrime, isPrime+1000, true);
    isPrime[0] = isPrime[1] = false;

    for (int i = 2; i*i < 1000; ++i) {
        if (isPrime[i]) {
            for (int j = i*i; j < 1000; j += i) {
                isPrime[j] = false;
            }
        }
    }

    int T;
    scanf("%d", &T);

    while (T--) {
        int k;
        scanf("%d", &k);
        char str[k+1];
        scanf("%s", str);

        std::map<int, int> counter;
        for (int i = 1; i <= 9; ++i) {
            counter[i] = 0;
        }
        for (int i = 0; i < k; ++i) {
            counter[str[i]-'0']++;
        }

        if (counter[1]) {
            printf("1\n1\n");
        } else if (counter[9]) {
            printf("1\n9\n");
        } else if (counter[4]) {
            printf("1\n4\n");
        } else if (counter[6]) {
            printf("1\n6\n");
        } else if (counter[8]) {
            printf("1\n8\n");
        } else if (counter[2] >= 2) {
            printf("2\n22\n");
        } else if (counter[3] >= 2) {
            printf("2\n33\n");
        } else if (counter[5] >= 2) {
            printf("2\n55\n");
        } else if (counter[7] >= 2) {
            printf("2\n77\n");
        } else {
            std::string s(str);
            int origin = std::stoi(s);
            for (int i = 1; i <= origin; ++i) {
                std::string iStr = std::to_string(i);
                if (isSubsequence(s, iStr) && !isPrime[i]) {
                    printf("%d\n%s\n", (int)iStr.size(), iStr.c_str());
                    break;
                }
            }
            // bool printed = false;
            // for (int i = 0; i < k; ++i) {
            //     std::string sub = s.substr(0, i) + s.substr(i+1);
            //     if (!isPrime[std::stoi(sub)]) {
            //         printf("%d\n%s\n", k-1, sub.c_str());
            //         printed = true;
            //         break;
            //     }
            // }

            // if (!printed) {
            //     printf("%d\n%s\n", k, str);
            // }
        }
    }

    return 0;
}
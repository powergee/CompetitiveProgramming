#include <iostream>
#include <unordered_set>

int main() {
    int k, n;
    scanf("%d", &k);
    scanf("%d", &n);

    std::unordered_set<int> numbers[9];
    int basis = k;
    for (int i = 1; i < 9; ++i) {
        numbers[i].insert(basis);
        basis = basis*10 + k;
    }

    for (int i = 1; i < 9; ++i) {
        for (int j = 1; i+j < 9; ++j) {
            for (int num1 : numbers[i]) {
                for (int num2 : numbers[j]) {
                    numbers[i+j].insert(num1+num2);
                    numbers[i+j].insert(num1*num2);

                    if (num1 > num2) {
                        numbers[i+j].insert(num1-num2);
                    }
                    if (num1 < num2) {
                        numbers[i+j].insert(num2-num1);
                    }

                    if (num1 > num2) {
                        numbers[i+j].insert(num1/num2);
                    } else {
                        numbers[i+j].insert(num2/num1);
                    }
                }
            }
        }
    }

    while (n--) {
        int q;
        scanf("%d", &q);

        int found = 0;
        for (int i = 1; i < 9; ++i) {
            if (numbers[i].find(q) != numbers[i].end()) {
                found = i;
                break;
            }
        }

        if (found == 0) {
            printf("NO\n");
        } else {
            printf("%d\n", found);
        }
    }

    return 0;
}
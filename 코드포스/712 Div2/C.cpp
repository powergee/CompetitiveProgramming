#include <iostream>
#include <vector>

char flip(char p) {
    if (p == '(') {
        return ')';
    } else {
        return '(';
    }
}

bool isValid(std::vector<char>& str, int n) {
    int count = 0;

    for (int i = 0; i < n; ++i) {
        if (str[i] == '(') {
            ++count;
        } else {
            --count;
        }

        if (count < 0) {
            return false;
        }
    }

    return count == 0;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int T;
    std::cin >> T;

    while (T--) {
        int n;
        std::string input;
        std::cin >> n >> input;

        std::vector<char> r1(n+1, '\0');
        std::vector<char> r2(n+1, '\0');
        char zeroPar = '(';

        for (int i = 0; i < n; ++i) {
            if (input[i] == '0') {
                r1[i] = zeroPar;
                zeroPar = flip(zeroPar);
                r2[i] = zeroPar;
            } else {
                if (i+1 < n && input[i+1] == '0') {
                    r1[i] = r2[i] = '(';
                } else if (i-1 >= 0 && input[i-1] == '0') {
                    r1[i] = r2[i] = ')';
                }
            }
        }

        int left = 0, right = n-1;
        while (left+1 < n && input[left] == '0') {
            ++left;
        }
        while (right-1 >= 0 && input[right] == '0') {
            --right;
        }

        while (left < right) {
            r1[left] = r2[left] = '(';
            r1[right] = r2[right] = ')';

            do {
                ++left;
            } while (left+1 < n && input[left] == '0');
            do {
                --right;
            } while (right-1 >= 0 && input[right] == '0');
        }

        if (isValid(r1, n) && isValid(r2, n)) {
            std::cout << "YES\n";
            std::cout << &r1[0] << '\n' << &r2[0] << '\n';
        } else {
            std::cout << "NO\n";
        }
    }
}
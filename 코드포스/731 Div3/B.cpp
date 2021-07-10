#include <iostream>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        std::string word;
        std::cin >> word;
        int n = word.size();

        int start = word.find('a');
        bool yes = true;
        if (start == std::string::npos) {
            yes = false;
        } else {
            int left = start-1;
            int right = start+1;
            int prev = 'a';
            
            while (left != -1 && right != n) {
                if (word[left] == prev+1) {
                    left--;
                    prev++;
                } else if (word[right] == prev+1) {
                    right++;
                    prev++;
                } else {
                    yes = false;
                    goto PRINT;
                }
            }

            while (left != -1) {
                if (word[left] == prev+1) {
                    left--;
                    prev++;
                } else {
                    yes = false;
                    goto PRINT;
                }
            }

            while (right != n) {
                if (word[right] == prev+1) {
                    right++;
                    prev++;
                } else {
                    yes = false;
                    goto PRINT;
                }
            }
        }

        PRINT:
        if (yes) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
}
#include <iostream>
#include <string>

int main() {
    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t) {
        int n;
        std::string str;
        std::cin >> n >> str;
        
        int answer = 0;
        int start = str.find_first_not_of('F');
        if (start < n) {
            char curr = str[start];
            for (int i = start; i < n; ++i) {
                if (str[i] == 'F') {
                    continue;
                } else if (str[i] != curr) {
                    ++answer;
                    curr = str[i];
                }
            }
        }
        printf("Case #%d: %d\n", t, answer);
    }
    
    return 0;
}
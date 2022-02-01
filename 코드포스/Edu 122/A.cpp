#include <iostream>
#include <string>

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);

        int minChange = INT32_MAX;
        std::string minStr;
        std::string nStr = std::to_string(n);
        for (int mult = 7; mult <= 999; mult += 7) {
            std::string mStr = std::to_string(mult);
            if (nStr.size() == mStr.size()) {
                int change = 0;
                for (int i = 0; i < nStr.size(); ++i) {
                    if (nStr[i] != mStr[i]) {
                        ++change;
                    }
                }
                if (change < minChange) {
                    minChange = change;
                    minStr = mStr;
                }
            }
        }

        printf("%s\n", minStr.c_str());
    }
    return 0;
}
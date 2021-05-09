#include <iostream>
#include <algorithm>
#include <cstring>

bool getTestCase(char* a, char* b) {
    std::fill(a, a+11, '\0');
    std::fill(b, b+11, '\0');
    scanf("%s %s", a, b);
    return (std::stoi(a) != 0 || std::stoi(b) != 0);
} 

int main() {
    char a[11], b[11], carry[12];
    while (getTestCase(a, b)) {
        std::fill(carry, carry+12, '\0');
        int aLen = strlen(a);
        int bLen = strlen(b);
        int length = std::max(aLen, bLen);
        
        std::fill(a+aLen, a+length, '0');
        std::fill(b+bLen, b+length, '0');
        std::reverse(a, a+aLen);
        std::reverse(b, b+bLen);

        int answer = 0;
        for (int i = 0; i < length; ++i) {
            char sum = (a[i]-'0') + (b[i]-'0') + carry[i];
            if (sum > 9) {
                answer++;
                carry[i+1]++;
            }
        }
        printf("%d\n", answer);
    }

    return 0;
}
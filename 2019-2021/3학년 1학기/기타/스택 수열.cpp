#include <iostream>
#include <stack>
#include <vector>

int main() {
    std::stack<int> s;
    std::vector<char> answer;
    bool success = true;
    int remain = 1;
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n && success; ++i) {
        int req;
        scanf("%d", &req);

        while (remain <= req) {
            s.push(remain++);
            answer.push_back('+');
        }

        if (s.empty() || s.top() != req) {
            success = false;
        } else {
            s.pop();
            answer.push_back('-');
        }
    }

    if (success) {
        for (char ch : answer) {
            printf("%c\n", ch);
        }
    } else {
        printf("NO");
    }

    return 0;
}
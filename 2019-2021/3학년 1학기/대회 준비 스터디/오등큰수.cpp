#include <iostream>
#include <stack>

int arr[1000000];
int count[1000001];
int answer[1000000];

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
        count[arr[i]]++;
        answer[i] = -1;
    }

    std::stack<int> s;
    s.push(0);

    for (int i = 1; i < n; ++i) {
        while (!s.empty() && count[arr[s.top()]] < count[arr[i]]) {
            answer[s.top()] = arr[i];
            s.pop();
        }
        s.push(i);
    }

    for (int i = 0; i < n; ++i) {
        printf("%d ", answer[i]);
    }

    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

int n, m;
int arr[8];
std::set<std::vector<int>> answers;
std::vector<int> selected;

void findCases(int start) {
    if (selected.size() == m) {
        answers.insert(selected);
    } else if (start != n) {
        selected.push_back(arr[start]);
        findCases(start);
        selected.pop_back();
        findCases(start+1);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    std::sort(arr, arr+n);
    findCases(0);

    for (auto& ans : answers) {
        for (int v : ans) {
            printf("%d ", v);
        }
        printf("\n");
    }

    return 0;
}
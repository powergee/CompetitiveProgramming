#include <iostream>
#include <vector>
#include <set>

int n, m;
int arr[8];
std::set<std::vector<int>> answers;
std::vector<int> selected;
bool used[8];

void findAll() {
    if (selected.size() == m) {
        answers.insert(selected);
    } else {
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                used[i] = true;
                selected.push_back(arr[i]);
                findAll();
                selected.pop_back();
                used[i] = false;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    findAll();
    for (auto& ans : answers) {
        for (int v : ans) {
            printf("%d ", v);
        }
        printf("\n");
    }

    return 0;
}
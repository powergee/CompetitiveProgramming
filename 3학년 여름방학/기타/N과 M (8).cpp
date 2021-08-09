#include <iostream>
#include <algorithm>
#include <vector>

int n, m;
int arr[8];
std::vector<int> selected;

void printCases(int start) {
    if (selected.size() == m) {
        for (int s : selected) {
            printf("%d ", s);
        }
        printf("\n");
    } else if (start != n) {
        selected.push_back(arr[start]);
        printCases(start);
        selected.pop_back();
        printCases(start+1);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr+i);
    }
    std::sort(arr, arr+n);
    printCases(0);

    return 0;
}
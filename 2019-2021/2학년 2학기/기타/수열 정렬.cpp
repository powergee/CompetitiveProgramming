#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
    int n;
    scanf("%d", &n);

    std::vector<int> arr;
    for (int i = 0; i < n; ++i)
    {
        int val;
        scanf("%d", &val);
        arr.push_back(val);
    }

    std::vector<int> sorted = arr;
    std::sort(sorted.begin(), sorted.end());
    std::vector<bool> selected(n, false);

    for (int i = 0; i < n; ++i)
    {
        int found;
        for (found = 0; found < n; ++found)
        {
            if (!selected[found] && arr[i] == sorted[found])
                break;
        }

        selected[found] = true;
        printf("%d ", found);
    }

    return 0;
}
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> arr;
std::vector<int> original;

int GetIndex(int val)
{
    return std::lower_bound(arr.begin(), arr.end(), val) - arr.begin();
}

int main()
{
    int n;
    scanf("%d", &n);

    while (n--)
    {
        int input;
        scanf("%d", &input);
        arr.push_back(input);
        original.push_back(input);
    }

    std::sort(arr.begin(), arr.end());
    arr.erase(std::unique(arr.begin(), arr.end()), arr.end());

    for (int val : original)
        printf("%d ", GetIndex(val));
}
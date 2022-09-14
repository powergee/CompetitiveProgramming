#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

int arr[500000];
int count[8001];

int main()
{
    int n, min = 4001, max = -4001;
    long long sum = 0;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        scanf("%d", arr + i);
        sum += arr[i];
        min = std::min(min, arr[i]);
        max = std::max(max, arr[i]);
        ++count[arr[i] + 4000];
    }

    std::sort(arr, arr + n);

    int average = (int)round((double)sum / n);
    int median = arr[n/2];
    int range = max - min;

    std::vector<int> mode;
    int modeCount = -1;

    for (int i = 0; i < 8001; ++i)
    {
        if (modeCount < count[i])
        {
            mode.resize(0);
            mode.push_back(i - 4000);
            modeCount = count[i];
        }
        else if (modeCount == count[i])
            mode.push_back(i - 4000);
    }

    printf("%d\n%d\n%d\n%d", average, median, (mode.size() > 1 ? mode[1] : mode[0]), range);
}
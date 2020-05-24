#include <iostream>
#include <vector>

std::vector<int> arr;
std::vector<int> temp;

bool Compare(int a, int b)
{
    return a < b;
}

void MergeSort(int left, int right)
{
    if (left == right)
        return;
    
    int length = right - left + 1;
    int med = (left + right) / 2;
    MergeSort(left, med);
    MergeSort(med + 1, right);

    int i = left, j = med + 1, pos = 0;
    while (pos < length)
    {
        if (Compare(arr[i], arr[j]))
            temp[pos++] = arr[i++];
        else
            temp[pos++] = arr[j++];

        if (i > med)
            while (j <= right)
                temp[pos++] = arr[j++];
                
        else if (j > right)
            while (i <= med)
                temp[pos++] = arr[i++];
    }

    for (int k = 0; k < length; ++k)
        arr[left + k] = temp[k];
}

int main()
{
    int n;
    scanf("%d", &n);
    arr.resize(n);
    temp.resize(n);

    for (int i = 0; i < n; ++i)
        scanf("%d", &arr[i]);

    MergeSort(0, n - 1);
    for (int i = 0; i < n; ++i)
        printf("%d\n", arr[i]);
}
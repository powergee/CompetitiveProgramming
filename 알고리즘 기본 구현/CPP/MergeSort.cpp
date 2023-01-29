#include <vector>
#include <functional>

template<typename T, typename Comparator>
void _MergeSort(int left, int right, std::vector<T>& arr, Comparator compare, std::vector<T>& temp)
{
    if (left == right)
        return;
    
    int length = right - left + 1;
    int med = (left + right) / 2;
    _MergeSort(left, med, arr, compare, temp);
    _MergeSort(med + 1, right, arr, compare, temp);

    int i = left, j = med + 1, pos = 0;
    while (pos < length)
    {
        temp[pos++] = (compare(arr[i], arr[j]) ? arr[i++] : arr[j++]);
        while (i > med && j <= right)
            temp[pos++] = arr[j++];
        while (j > right && i <= med)
            temp[pos++] = arr[i++];
    }

    for (int k = 0; k < length; ++k)
        arr[left + k] = temp[k];
}

template<typename T, typename Comparator = std::less<T>>
void MergeSort(int left, int right, std::vector<T>& arr)
{
    std::vector<T> temp(right-left+1);
    Comparator compare;
    _MergeSort(left, right, arr, compare, temp);
}
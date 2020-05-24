#include <iostream>
#include <algorithm>
#include <vector>
#define ARR_SIZE 20
#define SELECT_COUNT 10

int arr[ARR_SIZE];
std::vector<std::vector<int>> stlResult;
std::vector<std::vector<int>> recResult;

void STL_Combination()
{
    bool select[ARR_SIZE];
    std::fill(select, select + ARR_SIZE - SELECT_COUNT, false);
    std::fill(select + ARR_SIZE - SELECT_COUNT, select + ARR_SIZE, true);

    
}

int main()
{
    for (int i = 0; i < ARR_SIZE; ++i)
        arr[i] = i + 1;

    // 1. STL을 이용한 방법
    
}
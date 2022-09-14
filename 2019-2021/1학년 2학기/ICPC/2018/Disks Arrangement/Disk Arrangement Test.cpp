#include <iostream>
#include <ctime>
#include <cmath>
#include <algorithm>

std::pair<double, int>* nums;
std::pair<double, int>* minPer;
int N;

int main(int argc, char** argv)
{
    if (argc == 1)
    {
        scanf("%d", &N);
    }
    else
        N = atoi(argv[1]);

    nums = new std::pair<double, int>[N];
    minPer = new std::pair<double, int>[N];


    srand((unsigned int)time(0));

    for (int i = 0; i < N; ++i)
    {
        nums[i].first = rand();
    }

    std::sort(nums, nums + N);

    for (int i = 0; i < N; ++i)
    {
        nums[i].second = i;
    }

    double min = 0x7fffffff;

    do
    {
        double opt = nums[0].first + nums[N - 1].first;
        for (int i = 1; i < N; ++i)
        {
            opt += sqrt(pow(nums[i].first + nums[i-1].first, 2) - pow(nums[i].first - nums[i-1].first, 2));
        }

        if (min > opt)
        {
            std::copy(nums, nums + N, minPer);
            min = opt;
        }
    } while (std::next_permutation(nums, nums + N));
    
    for (int i = 0; i < N; ++i)
    {
        printf("%d ", minPer[i].second);
    }
    printf("\n");
    for (int i = 0; i < N; ++i)
    {
        printf("%.0lf ", minPer[i].first);
    }
    printf("\n%lf", min);

    delete[] nums;
    delete[] minPer;
}
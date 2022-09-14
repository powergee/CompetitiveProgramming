#include <iostream>
#include <algorithm>
using namespace std;

bool IsGood(char* str, int length)
{
    for (int i = 0; i < length; ++i)
    {
        for (int j = 1; j < (length - i)/2; ++j)
        {
            bool same = true;
            for (int k = 0; k < j; ++k)
            {
                if (str[i + k] != str[i+j+k])
                {
                    same = false;
                    break;
                }
            }

            if (same)
                return true;
        }
    }

    return false;
}

int main()
{
    printf("%d", IsGood((char*)"123", 3));
    printf("%d", IsGood((char*)"11", 2));
    printf("%d", IsGood((char*)"123123", 6));
}
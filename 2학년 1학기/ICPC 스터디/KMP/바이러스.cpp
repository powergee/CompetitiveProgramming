#include <iostream>
#include <vector>

std::vector<int> GetPI(std::vector<int> vec)
{
    int length = (int)vec.size();
    std::vector<int> result(length, 0);

    int start = 1, matched = 0;
    while (start + matched < length)
    {
        if (vec[start + matched] == vec[matched])
        {
            ++matched;
            result[start + matched - 1] = matched;
        }
        else
        {
            if (matched == 0)
                ++start;
            else
            {
                start += matched - vec[matched - 1];
                matched = result[matched - 1];
            }
        }
    }

    return result;
}

bool FindVirus(std::vector<int> target, std::vector<int> dest)
{
    int n = target.size(), m = dest.size();

    std::vector<int> answer;
    std::vector<int> pi = GetPI(dest);

    int begin = 0, matched = 0;
    while (begin + m <= n)
    {
        if (matched < m && target[begin + matched] = dest[matched])
        {
            ++matched;
            if (matched == m)
                return true;
        }
        else
        {
            if 
        }
    }
}

int main()
{


    return 0;
}
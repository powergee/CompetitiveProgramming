#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <vector>

std::string input[3];
long long coeff[10];
std::unordered_map<char, int> indexMap;

int GetIndex(char name)
{
    auto it = indexMap.find(name);
    // 찾을 수 없음.
    if (it == indexMap.end())
    {
        int count = indexMap.size();
        return indexMap[name] = count;
    }
    // 인덱스를 찾았음.
    else 
        return it->second;
}

int IntPow(int x, int y)
{
    int result = 1;
    while (y--)
        result *= x;

    return result;
}

// add가 true이면 계수를 그냥 더하지만, false이면 계수를 뺌.
bool AddCoeff(const std::string& str, bool add)
{
    for (int i = 0; i < str.size(); ++i)
    {
        int index = GetIndex(str[i]);

        if (index == 10)
            return false;

        coeff[index] += IntPow(10, str.size() - i - 1) * (add ? 1 : -1);
    }

    return true;
}

int main()
{
    for (int i = 0; i < 3; ++i)
        std::cin >> input[i];

    if (AddCoeff(input[0], true) && AddCoeff(input[1], true) && AddCoeff(input[2], false))
    {
        std::vector<char> combination;
        for (int i = 0; i < 10; ++i)
        {
            if (i < indexMap.size())
                combination.push_back(1);
            else combination.push_back(0);
        }

        std::sort(combination.begin(), combination.end());

        do
        {
            std::vector<int> selected;
            for (int i = 0; i < 10; ++i)
            {
                if (combination[i])
                    selected.push_back(i);
            }

            do
            {
                long long sum = 0;
                for (int i = 0; i < indexMap.size(); ++i)
                {
                    sum += coeff[i] * selected[i];
                }

                if (sum == 0)
                {
                    printf("YES");
                    return 0;
                }
            } while (std::next_permutation(selected.begin(), selected.end()));
        } while (std::next_permutation(combination.begin(), combination.end()));
        
    }

    printf("NO");

    return 0;
}
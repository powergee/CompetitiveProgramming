#include <iostream>
#include <string>
#include <vector>
#include <stack>

int main()
{
    std::string input;
    std::cin >> input;

    std::vector<std::pair<char, int>> segList;
    std::pair<char, int> current = {input[0], 1};
    for (int i = 1; i < (int)input.size(); ++i)
    {
        if (current.first == input[i])
            ++current.second;
        else
        {
            segList.push_back(current);
            current = {input[i], 1};
        }
    }
    segList.push_back(current);

    int left = 0, right = (int)segList.size()-1;
    int result = 0;
    while (left <= right)
    {
        if (left == right && segList[left].second >= 2)
            result = segList[left].second+1;

        else if (segList[left].first != segList[right].first ||
            segList[left].second + segList[right].second < 3)
            break;
        
        ++left;
        --right;
    }

    std::cout << result;

    return 0;
}
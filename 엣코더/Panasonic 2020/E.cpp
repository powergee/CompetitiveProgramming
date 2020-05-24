#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

bool Same(char ch1, char ch2)
{
    if (ch1 == '?' || ch2 == '?')
        return true;
    else return ch1 == ch2;
}

int GetMaxCommon(std::string& front, std::string& back)
{
    
    int len = 1;
    for (; (int)front.size() - 1 - len >= 0 && len < (int)back.size() && Same(front[(int)front.size() - 1 - len], back[len]); ++len);
    return len;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string str[3];
    std::cin >> str[0] >> str[1] >> str[2];

    std::vector<int> seq;
    seq.push_back(0);
    seq.push_back(1);
    seq.push_back(2);

    int minLen = 1e9;
    do
    {
        std::string& first = str[seq[0]], med = str[seq[1]], back = str[seq[2]];
        int l1 = GetMaxCommon(first, med);
        int l2 = GetMaxCommon(med, back);
        int currLen = (int)first.size() - l1 + (int)med.size() - l2 + (int)back.size();
        minLen = std::min(currLen, minLen);
    } while (std::next_permutation(seq.begin(), seq.end()));

    std::cout << minLen;

    return 0;
}
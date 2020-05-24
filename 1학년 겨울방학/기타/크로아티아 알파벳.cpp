#include <iostream>
#include <string>

bool Check(int pos, const std::string& str, int& count, const std::string& word)
{
    if ((int)str.size() <= pos + (int)word.size() - 1)
        return false;

    for (int i = 0; i < (int)word.size(); ++i)
        if (word[i] != str[i + pos])
            return false;

    ++count;
    return true;
}

int main()
{
    std::string str;
    std::cin >> str;
    int count = 0;

    for (int i = 0; i < (int)str.size();)
    {
        if (Check(i, str, count, "c=")) i += 2;
        else if (Check(i, str, count, "c-")) i += 2;
        else if (Check(i, str, count, "dz=")) i += 3;
        else if (Check(i, str, count, "d-")) i += 2;
        else if (Check(i, str, count, "lj")) i += 2;
        else if (Check(i, str, count, "nj")) i += 2;
        else if (Check(i, str, count, "s=")) i += 2;
        else if (Check(i, str, count, "z=")) i += 2;
        else { ++i; ++count; }
    }

    printf("%d", count);

    return 0;
}
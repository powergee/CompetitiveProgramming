#include <iostream>
#include <algorithm>
#include <string>

std::string words[50];
std::string start[50];
std::string end[50];
std::string con[50];

bool GetParent_Start(std::string& s1, std::string& s2, std::string& result)
{
    int n = std::min(s1.size(), s2.size());
    for (unsigned i = 0; i < n; ++i)
    {
        if (s1[i] != s2[i])
            return false;
    }
    result = s1.size() > s2.size() ? s1 : s2;
    return true;
}

bool GetParent_End(std::string& s1, std::string& s2, std::string& result)
{
    int n = std::min(s1.size(), s2.size());
    for (int i = 0; i < n; ++i)
    {
        if (s1[s1.size() - i - 1] != s2[s2.size() - i - 1])
            return false;
    }
    result = s1.size() > s2.size() ? s1 : s2;
    return true;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    for (int c = 1; c <= T; ++c)
    {
        int n;
        std::cin >> n;

        for (int i = 0; i < n; ++i)
        {
            std::cin >> words[i];
            size_t startPos = words[i].find_first_not_of('*');
            size_t endPos = words[i].find_last_of('*');
            start[i] = words[i].substr(0, startPos - 1);
            end[i] = words[i].substr(endPos + 1);
            if (endPos > startPos)
                con[i] = words[i].substr(startPos, endPos - startPos);
            else con[i] = "";
        }

        std::string startPar = "", endPar = "";
        bool success = true;
        for (int i = 0; i < n && success; ++i)
        {
            if (start[i].size() > 0 && !GetParent_Start(startPar, start[i], startPar))
                success = false;
            if (end[i].size() > 0 && !GetParent_End(endPar, end[i], endPar))
                success = false;
        }

        if (success)
        {
            std::cout << "Case #" << c << ": " << startPar;
            for (int i = 0; i < n; ++i)
            {
                con[i].erase(std::remove(con[i].begin(), con[i].end(), '*'), con[i].end());
                std::cout << con[i];
            }
            std::cout << endPar << '\n';
        }
        else std::cout << "Case #" << c << ": " << "*\n";
    }

    return 0;
}
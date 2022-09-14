#include <iostream>
#include <set>

struct StringCompare
{
    bool operator()(const std::string& s1, const std::string& s2)
    {
        if (s1.size() == s2.size())
            return s1 < s2;
        else return s1.size() < s2.size();
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::set<std::string, StringCompare> words;
    std::cin >> n;

    while (n--)
    {
        std::string input;
        std::cin >> input;
        words.insert(input);
    }

    for (const std::string& word : words)
        std::cout << word << '\n';

    return 0;
}
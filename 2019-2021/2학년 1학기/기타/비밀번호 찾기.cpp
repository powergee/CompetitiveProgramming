#include <iostream>
#include <map>
#include <string>

int n, m;
std::map<std::string, std::string> pwBook;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;

    for (int i = 0; i < n; ++i)
    {
        std::string domain, pw;
        std::cin >> domain >> pw;
        pwBook[domain] = pw;
    }

    for (int i = 0; i < m; ++i)
    {
        std::string domain;
        std::cin >> domain;
        std::cout << pwBook[domain] << '\n';
    }

    return 0;
}
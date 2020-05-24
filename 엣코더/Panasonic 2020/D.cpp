#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

std::vector<std::string> result;



int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    for (int divCount = 1; divCount <= n; ++divCount)
    {

    }

    std::sort(result.begin(), result.end());
    for (std::string& s : result)
        std::cout << s << '\n';

    return 0;
}
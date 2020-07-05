#include <iostream>
#include <string>
#include <map>

std::map<std::string, int> count;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        std::string result;
        std::cin >> result;
        count[result] += 1;
    }

    std::cout << "AC x " << count["AC"] << "\n";
    std::cout << "WA x " << count["WA"] << "\n";
    std::cout << "TLE x " << count["TLE"] << "\n";
    std::cout << "RE x " << count["RE"];
}
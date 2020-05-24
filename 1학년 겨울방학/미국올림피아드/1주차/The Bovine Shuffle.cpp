#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

std::vector<int> inverse;
std::vector<std::string> cows;
std::vector<std::string> moved[3];

int main()
{
    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

    int n;
    std::cin >> n;

    inverse.resize(n + 1);
    cows.resize(n + 1);

    for (int i = 1; i <= n; ++i)
    {
        int from;
        std::cin >> from;
        inverse[from] = i;
    }

    for (int i = 1; i <= n; ++i)
        std::cin >> cows[i];

    std::vector<std::string>* current = &cows;
    for (int move = 0; move < 3; ++move)
    {
        moved[move].resize(n + 1);

        for (int i = 1; i <= n; ++i)
            moved[move][inverse[i]] = (*current)[i];

        current = &moved[move];
    }

    for (int i = 1; i <= n; ++i)
        std::cout << (*current)[i] << '\n';

    return 0;
}
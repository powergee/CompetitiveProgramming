#include <iostream>
#include <string>
#include <vector>
#include <numeric>

std::vector<int> getFail(std::string& str)
{
    std::vector<int> fail(str.size(), 0);
    for (int i = 1, j = 0; i < (int)str.size(); ++i)
    {
        while (j > 0 && str[i] != str[j])
            j = fail[j-1];
        if (str[i] == str[j])
            fail[i] = ++j;
    }

    return fail;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::string str;
    std::cin >> n >> str;

    auto fail = getFail(str);
    int word = n - fail.back();
    std::cout << word;

    return 0;
}
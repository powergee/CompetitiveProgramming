#include <string>
#include <vector>
#include <iostream>

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
    std::string str;

    while (std::cin >> str, str != ".") {
        auto fail = getFail(str);
        int last = fail.back();
        int word = str.size() - last;

        if (last != 0 && str.size() % word == 0) {
            printf("%d\n", (int)str.size() / word);
        } else {
            printf("1\n");
        }
    }

    return 0;
}
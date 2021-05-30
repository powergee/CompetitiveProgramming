#include <iostream>
#include <string>
#include <vector>

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

bool KMP(std::string& para, std::string& target)
{
    auto fail = getFail(target);

    for (int i = 0, j = 0; i < (int)para.size(); ++i) {
        while (j > 0 && para[i] != target[j])
            j = fail[j-1];
        if (para[i] == target[j]) {
            if (j == (int)target.size()-1) {
                return true;
            }
            else j++;
        }
    }
    return false;
}

std::string subBetween(std::string str, int l, int r) {
    return str.substr(l, r-l+1);
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str;
    std::cin >> str;

    auto fail = getFail(str);

    if (fail.back() == 0 || str.size() <= 2) {
        std::cout << "-1";
    } else {
        int wLen1 = fail.back();
        std::string para1 = str.substr(1, str.size()-2);
        std::string word1 = str.substr(0, wLen1);
        bool k1 = KMP(para1, word1);

        if (k1) {
            std::cout << word1;
        } else {
            int wLen2 = getFail(word1).back();
            std::string word2 = str.substr(0, wLen2);
            bool k2 = KMP(para1, word2);
            if (k2) {
                std::cout << word2;
            } else {
                std::cout << "-1";
            }
        }
    }
}
#include <iostream>
#include <string>

void printBinary(char oc, bool includeZero)
{
    const char* body = "";
    const char* zeros = "";
    switch (oc)
    {
    case '0':
        zeros = "00";
        body = "0";
        break;
    case '1':
        zeros = "00";
        body = "1";
        break;
    case '2':
        zeros = "0";
        body = "10";
        break;
    case '3':
        zeros = "0";
        body = "11";
        break;
    case '4':
        zeros = "";
        body = "100";
        break;
    case '5':
        zeros = "";
        body = "101";
        break;
    case '6':
        zeros = "";
        body = "110";
        break;
    case '7':
        zeros = "";
        body = "111";
        break;
    }

    if (includeZero)
        std::cout << zeros;
    std::cout << body;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string input;
    std::cin >> input;

    printBinary(input[0], false);
    for (int i = 1; i < (int)input.size(); ++i)
        printBinary(input[i], true);

    return 0;
}
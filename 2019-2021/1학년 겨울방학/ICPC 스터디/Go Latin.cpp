#include <iostream>
#include <string>

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        std::string s, result;
        std::cin >> s;
        int length = s.size();

        if (s[length - 1] == 'e' && s[length - 2] == 'n')
            result = s.substr(0, length - 2) + "anes";
        else
        {
            switch (s[length - 1])
            {
            case 'a':
            case 'o':
            case 'u':
                result = s + "s";
                break;

            case 'y':
            case 'i':
                result = s.substr(0, length - 1) + "ios";
                break;

            case 'r':
            case 'l':
            case 'v':
                result = s + "es";
                break;

            case 'n':
                result = s.substr(0, length - 1) + "anes";
                break;

            case 't':
            case 'w':
                result = s + "as";
                break;
            
            default:
                result = s + "us";
                break;
            }
        }

        std::cout << result << "\n";
    }

    return 0;
}
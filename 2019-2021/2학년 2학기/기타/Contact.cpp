#include <iostream>
#include <string>

bool verify(int start, std::string& signal)
{
    if ((int)signal.size() <= start)
        return true;
    
    if (signal[start] == '1' && signal[start+1] == '0')
    {
        for (int i = start+2; i < (int)signal.size(); ++i)
        {
            if (signal[i] == '0')
            {
                for (int j = i+1; j < (int)signal.size(); ++j)
                {
                    if (signal[j] == '1')
                    {
                        if (verify(j+1, signal))
                            return true;
                    }
                    else break;
                }
            }
            else break;
        }
    }

    if (signal[start] == '0' && signal[start+1] == '1')
        return verify(start+2, signal);

    return false;
}

int main()
{
    int n;
    std::string signal;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        std::cin >> signal;
        std::cout << (verify(0, signal) ? "YES\n" : "NO\n");
    }

    return 0;
}
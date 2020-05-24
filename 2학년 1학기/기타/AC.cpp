#include <iostream>
#include <sstream>
#include <deque>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    
    int T;
    std::cin >> T;

    while (T--)
    {
        int n;
        std::deque<int> arr;
        std::string funcStr, arrStr;
        std::cin >> funcStr >> n >> arrStr;

        if (n > 0)
        {
            std::stringstream ss(arrStr);
            for (int i = 0; i < n; ++i)
            {
                int val;
                char junk;
                ss >> junk >> val;
                arr.push_back(val);
            }
        }

        bool reversed = false;
        bool error = false;
        for (char func : funcStr)
        {
            if (func == 'R')
                reversed = !reversed;
            else
            {
                if (arr.empty())
                    error = true;
                else if (reversed)
                    arr.pop_back();
                else arr.pop_front();
            }

            if (error)
                break;
        }

        if (error)
            std::cout << "error\n";
        else
        {
            std::cout << '[';
            while (!arr.empty())
            {
                int val;
                if (reversed)
                {
                    val = arr.back();
                    arr.pop_back();
                }
                else
                {
                    val = arr.front();
                    arr.pop_front();
                }
                std::cout << val;

                if (!arr.empty())
                    std::cout << ',';
            }
            std::cout << "]\n";
        }
    }

    return 0;
}
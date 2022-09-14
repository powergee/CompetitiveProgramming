#include <iostream>
#include <deque>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::deque<int> d;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        std::string comm;
        std::cin >> comm;

        if (comm == "push_front")
        {
            int x;
            std::cin >> x;
            d.push_front(x);
        }
        else if (comm == "push_back")
        {
            int x;
            std::cin >> x;
            d.push_back(x);
        }
        else if (comm == "pop_front")
        {
            if (d.empty())
                std::cout << -1 << '\n';
            else
            {
                std::cout << d.front() << '\n';
                d.pop_front();
            }
        }
        else if (comm == "pop_back")
        {
            if (d.empty())
                std::cout << -1 << '\n';
            else
            {
                std::cout << d.back() << '\n';
                d.pop_back();
            }
        }
        else if (comm == "size")
            std::cout << d.size() << '\n';
        else if (comm == "empty")
            std::cout << (d.empty() ? 1 : 0) << '\n';
        else if (comm == "front")
        {
            if (d.empty())
                std::cout << -1 << '\n';
            else
                std::cout << d.front() << '\n';
        }
        else if (comm == "back")
        {
            if (d.empty())
                std::cout << -1 << '\n';
            else
                std::cout << d.back() << '\n';
        }
    }

    return 0;
}
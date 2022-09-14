#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

struct Info
{
    int Age, Date;
    std::string Name;

    Info(int date, int age, std::string& name) : Age(age), Date(date), Name(name) {}

    bool operator<(const Info& i)
    {
        if (Age == i.Age)
            return Date < i.Date;
        else return Age < i.Age;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::vector<Info> vec;
    std::cin >> n;

    for (int i = 0; i < n; ++i)
    {
        int age;
        std::string name;
        std::cin >> age >> name;
        vec.emplace_back(i, age, name);
    }

    std::sort(vec.begin(), vec.end());

    for (auto ele : vec)
        std::cout << ele.Age << ' ' << ele.Name << '\n';

    return 0;
}
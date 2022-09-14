#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>

typedef long long Long;

class Fraction
{
private:
    Long num, den;

public:
    Fraction(Long n, Long d) : num(n), den(d) {}
    Fraction() : Fraction(0, 1) {}

    void reduce()
    {
        if (num == 0)
            den = 1;
        else
        {
            Long min = std::min(num, den);

            if (num % min == 0 && den % min == 0)
                num /= min, den /= min;
            else
                for (int i = 2; i <= sqrt(min); ++i)
                    if (num % i == 0 && den % i == 0)
                        num /= i, den /= i, --i;
        }
    }

    int toInt()
    {
        return num / den;
    }

    double toDouble()
    {
        return (double)num / den;
    }

    Fraction operator+(Fraction f)
    {
        return Fraction(num*f.den + f.num*den, den*f.den);
    }

    Fraction operator-(Fraction f)
    {
        return Fraction(num*f.den - f.num*den, den*f.den);
    }

    Fraction operator*(Fraction f)
    {
        return Fraction(num*f.num, den*f.den);
    }

    Fraction operator/(Fraction f)
    {
        return Fraction(num*f.den, den*f.num);
    }

    bool operator<(Fraction f)
    {
        return toDouble() < f.toDouble();
    }
};

std::unordered_map<std::string, std::pair<int, int>> places;
std::unordered_map<std::string, int> stations;

enum Status {outOfGas, capacityFull, running};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int a, b, c, n;
    std::cin >> a >> b >> c >> n;

    for (int i = 0; i < n; ++i)
    {
        std::cin >> std::ws;
        std::string line;
        std::getline(std::cin, line);
        auto firstBlank = line.find_last_of(' ');
        int y = std::stoi(line.substr(firstBlank + 1));
        auto secondBlank = line.find_last_of(' ', firstBlank - 1);
        int x = std::stoi(line.substr(secondBlank + 1, firstBlank - secondBlank - 1));
        places[line.substr(0, secondBlank)] = {x, y};
    }

    for (int i = 0; i < 3; ++i)
    {
        std::cin >> std::ws;
        std::string line;
        std::getline(std::cin, line);
        auto blank = line.find_last_of(' ');
        int fee = std::stoi(line.substr(blank + 1));
        stations[line.substr(0, blank)] = fee;
    }

    int k;
    std::cin >> k;

    std::unordered_multimap<std::string, int> passengers;
    int moved = 0, money = 0;
    Fraction remainingGas(a, 1);
    Status taxiStatus = running;
    std::string curr = "Taxi Garage";
    
    for (int i = 0; i < k; ++i)
    {
        std::cin >> std::ws;
        std::string line, dest;
        std::getline(std::cin, line);

        if (line[0] == 'P')
        {
            dest = line.substr(28, line.size() - 29);
            passengers.insert({dest, moved});
            if (passengers.size() > 3)
            {
                taxiStatus = capacityFull;
                break;
            }
        }
        else
        {
            dest = line.substr(6, line.size() - 7);
            auto destPos = places[dest], currPos = places[curr];
            int dist = abs(destPos.first - currPos.first) + abs(destPos.second - currPos.second);
            Fraction need(dist, c);
            if (remainingGas < need)
            {
                taxiStatus = outOfGas;
                break;
            }

            remainingGas = remainingGas - need;
            moved += dist;
            curr = dest;
        }

        std::unordered_multimap<std::string, int>::iterator pIter;
        while ((pIter = passengers.find(curr)) != passengers.end())
        {
            money += (moved - pIter->second) * b;
            passengers.erase(pIter);
        }

        if (stations.find(curr) != stations.end())
        {
            Fraction extra = Fraction(a, 1) - remainingGas;
            int fee = (extra * Fraction(stations[curr], 1)).toInt();
            if (fee <= money)
            {
                money -= fee;
                remainingGas = Fraction(a, 1);
            }
            else
            {
                remainingGas = remainingGas + Fraction(money, 1) / Fraction(stations[curr], 1);
                money = 0;
            }
        }

        remainingGas.reduce();
    }

    switch (taxiStatus)
    {
    case outOfGas:
        std::cout << "OUT OF GAS";
        break;
    
    case capacityFull:
        std::cout << "CAPACITY FULL";
        break;
    
    default:
        if (curr != "Taxi Garage")
            std::cout << "NOT IN GARAGE";
        else if (passengers.size() > 0)
            std::cout << "REMAINING PASSENGER";
        else
            std::cout << money;
        break;
    }

    return 0;
}
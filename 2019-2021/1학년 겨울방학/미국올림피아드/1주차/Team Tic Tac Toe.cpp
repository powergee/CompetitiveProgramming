#include <iostream>
#include <set>

std::set<unsigned int> indivWin;
std::set<unsigned int> twoWin;

void UpdateSet(const std::set<char>& cows)
{
    if (cows.size() == 2)
    {
        unsigned int i = 0, repre = 0;
        for (char cow : cows)
        {
            repre += ((int)cow) << (i * sizeof(char) * 8);
            ++i;
        }
        twoWin.insert(repre);
    }
    if (cows.size() == 1)
        indivWin.insert((unsigned int)*cows.begin());
}

int main()
{
    char tic[3][4];

    for (int row = 0; row < 3; ++row)
        scanf("%s", tic[row]);

    std::set<char> cows;

    for (int row = 0; row < 3; ++row)
    {
        cows.clear();
        for (int col = 0; col < 3; ++col)
            cows.insert(tic[row][col]);

        UpdateSet(cows);
    }

    for (int col = 0; col < 3; ++col)
    {
        cows.clear();
        for (int row = 0; row < 3; ++row)
            cows.insert(tic[row][col]);

        UpdateSet(cows);
    }

    cows.clear();
    cows.insert(tic[0][0]);
    cows.insert(tic[1][1]);
    cows.insert(tic[2][2]);

    UpdateSet(cows);

    cows.clear();
    cows.insert(tic[0][2]);
    cows.insert(tic[1][1]);
    cows.insert(tic[2][0]);

    UpdateSet(cows);

    printf("%d\n%d", indivWin.size(), twoWin.size());
    
    return 0;
}
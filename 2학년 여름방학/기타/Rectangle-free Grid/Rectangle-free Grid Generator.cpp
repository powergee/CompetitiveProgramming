#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>

const std::string PATH = "G:\\CompetitiveProgramming\\2학년 여름방학\\기타\\Rectangle-free Grid\\outputs\\";

struct Point
{
    int row, col;

    bool operator<(const Point& p) const
    {
        if (row == p.row)
            return col < p.col;
        return row < p.row;
    }

    bool operator==(const Point& p) const
    {
        return row == p.row && col == p.col;
    }
};

struct Square
{
    Point p1, p2;

    bool operator<(const Square& s) const
    {
        if (p1 == s.p1)
            return p2 < s.p2;
        return p1 < s.p1;
    }
};

int main()
{
    char grid[150][151];
    std::fill(&grid[0][0], &grid[0][0] + sizeof(grid) / sizeof(char), 'O');
    
    int n;
    for (n = 2; n <= 150; ++n)
    {
        
    }
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string PATH = "/home/hyeon/CompetitiveProgramming/2학년 여름방학/기타/Rectangle-free Grid/outputs/";
char grid[150][151];
int n = 150;
int count = 0;

bool isAbleToMark(int r, int c)
{
    if (grid[r][c] == 'O')
        return false;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (i == r || j == c)
                continue;
            
            if (grid[i][j] == 'O' &&
                grid[i][c] == 'O' &&
                grid[r][j] == 'O')
                return false;
        }
    }

    return true;
}

void fillLayer(int layer)
{
    for (int i = layer; i >= 0; --i)
    {
        // left up
        if (isAbleToMark(i, layer))
        {
            grid[i][layer] = 'O';
            ++count;
        }
        else
            grid[i][layer] = '.';
        
        if (isAbleToMark(layer, i))
        {
            grid[layer][i] = 'O';
            ++count;
        }
        else
            grid[layer][i] = '.';
        /*
        // left down
        if (isAbleToMark(n-1-i, layer))
            grid[n-1-i][layer] = 'O', ++count;
        else
            grid[n-1-i][layer] = '.';
        
        if (isAbleToMark(n-1-layer, i))
            grid[n-1-layer][i] = 'O', ++count;
        else
            grid[n-1-layer][i] = '.';

        // right up
        if (isAbleToMark(i, n-1-layer))
            grid[i][n-1-layer] = 'O', ++count;
        else
            grid[i][n-1-layer] = '.';
        
        if (isAbleToMark(layer, n-1-i))
            grid[layer][n-1-i] = 'O', ++count;
        else
            grid[layer][n-1-i] = '.';*/
    }
}

void dump(int size)
{
    std::ofstream output(PATH + std::to_string(size) + ".txt");
    output << size << std::endl;
    for (int i = 0; i < size; ++i)
        output << grid[i] << std::endl;
    output.close();
}

int main()
{
    grid[0][0] = '.';
    for (int layer = 1; layer < n; ++layer)
    {
        fillLayer(layer);
        dump(layer+1);
        printf("%d\n", count);
    }
}
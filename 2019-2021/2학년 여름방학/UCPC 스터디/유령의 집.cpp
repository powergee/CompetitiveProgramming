#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <cmath>

enum Direction {north = 0, east = 1, south = 2, west = 3};
enum Kind {outside, ghost, mirror, backMirror};
typedef long long Long;

Direction reflect(Kind k, Direction dir)
{
    if (k == mirror)
    {
        switch (dir)
        {
        case north:
            return east;
        case east:
            return north;
        case south:
            return west;
        case west:
            return south;
        }
    }
    else if (k == backMirror)
    {
        switch (dir)
        {
        case north:
            return west;
        case east:
            return south;
        case south:
            return east;
        case west:
            return north;
        }
    }
    return dir;
}

struct Node
{
    Node* next[4] = {nullptr, nullptr, nullptr, nullptr};
    Kind kind;
    int row, col;
    std::pair<Long, Long> dp[4] = {{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}};

    Node() { }

    Node(int r, int c, Kind k)
    {
        row = r;
        col = c;
        kind = k;
    }

    std::pair<Long, Long> findGhosts(Direction dir)
    {
        std::pair<Long, Long>& result = dp[dir];
        if (result.first != -1)
            return result;
        
        if (kind == ghost)
            result = {1, 0};
        else result = {0, 0};
        
        Direction nextDir = reflect(kind, dir);
        
        if (next[nextDir])
        {
            auto nextResult = next[nextDir]->findGhosts(nextDir);
            return result = {result.first + nextResult.first, nextResult.second + (nextResult.first * calcDist(next[nextDir]))};
        }
        else return result;
    }

    int calcDist(Node* other)
    {
        return std::abs(row - other->row) + std::abs(col - other->col);
    }
};

int n, m, k, q;
Node outNodes[4][300000];
Node* most[4][300000];
Node nodes[300000];

int main()
{
    scanf("%d %d %d %d", &n, &m, &k, &q);

    for (int i = 0; i < n; ++i)
    {
        outNodes[east][i] = Node(i, m, outside);
        outNodes[west][i] = Node(i, -1, outside);
        most[east][i] = &outNodes[east][i];
        most[west][i] = &outNodes[west][i];
    }

    for (int i = 0; i < m; ++i)
    {
        outNodes[north][i] = Node(-1, i, outside);
        outNodes[south][i] = Node(n, i, outside);
        most[north][i] = &outNodes[north][i];
        most[south][i] = &outNodes[south][i];
    }

    std::vector<std::tuple<int, int, char>> inputs;
    for (int i = 0; i < k; ++i)
    {
        int x, y;
        char c;
        scanf("%d %d %c", &x, &y, &c);
        inputs.push_back(std::make_tuple(x-1, y-1, c));
    }
    std::sort(inputs.begin(), inputs.end());

    for (int i = 0; i < k; ++i)
    {
        int row, col;
        char kChar;
        std::tie(row, col, kChar) = inputs[i];
        
        Kind kind = ghost;
        switch (kChar)
        {
        case '!':
            kind = ghost;
            break;
        case '/':
            kind = mirror;
            break;
        case '\\':
            kind = backMirror;
            break;
        }

        nodes[i] = Node(row, col, kind);

        nodes[i].next[north] = most[north][col];
        most[north][col]->next[south] = &nodes[i];
        most[north][col] = &nodes[i];

        nodes[i].next[west] = most[west][row];
        most[west][row]->next[east] = &nodes[i];
        most[west][row] = &nodes[i];
    }

    for (int i = 0; i < k; ++i)
    {
        if (!nodes[i].next[east])
        {
            nodes[i].next[east] = most[east][nodes[i].row];
            most[east][nodes[i].row]->next[west] = &nodes[i];
        }
        if (!nodes[i].next[south])
        {
            nodes[i].next[south] = most[south][nodes[i].col];
            most[south][nodes[i].col]->next[north] = &nodes[i];
        }
    }

    for (int i = 0; i < q; ++i)
    {
        char com[10];
        scanf("%s", com);

        std::pair<Long, Long> answer = {0, 0};
        switch (com[0])
        {
        case 'U':
            answer = outNodes[north][atoi(com + 1) - 1].findGhosts(south);
            break;
        
        case 'D':
            answer = outNodes[south][atoi(com + 1) - 1].findGhosts(north);
            break;
        
        case 'L':
            answer = outNodes[west][atoi(com + 1) - 1].findGhosts(east);
            break;
        
        case 'R':
            answer = outNodes[east][atoi(com + 1) - 1].findGhosts(west);
            break;
        
        default:
            break;
        }

        printf("%lld %lld\n", answer.first, answer.second);
    }

    return 0;
}
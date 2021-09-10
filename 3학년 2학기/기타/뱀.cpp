#include <iostream>
#include <deque>
#include <vector>

using Point = std::pair<int, int>;

enum Direction {
    Undefined, Left, Right, Up, Down
};

enum Cell {
    Empty, Apple, Body
};

Direction turnLeft(Direction dir) {
    switch (dir) {
    case Left: return Down;
    case Right: return Up;
    case Up: return Left;
    case Down: return Right;
    }
    return Undefined;
}

Direction turnRight(Direction dir) {
    return turnLeft(turnLeft(turnLeft(dir)));
}

Point movePoint(Point p, Direction dir) {
    switch (dir) {
    case Left: return { p.first, p.second-1 };
    case Right: return { p.first, p.second+1 };
    case Up: return { p.first-1, p.second };
    case Down: return { p.first+1, p.second };
    }
    return p;
}

class Game {
private:
    int size;
    std::vector<std::vector<Cell>> board;
    std::deque<Point> body;
    std::vector<Direction> timeline;
    Direction dir = Right;
    int time = 0;

public:
    Game(int n, std::vector<Point>& apples, std::vector<std::pair<int, char>> commands) {
        size = n;
        board.resize(n);
        for (int i = 0; i < n; ++i) {
            board[i].resize(n, Empty);
        }

        for (Point apple : apples) {
            auto[r, c] = apple;
            board[r][c] = Apple;
        }

        timeline.resize(commands.back().first+1, Undefined);
        for (auto comm : commands) {
            timeline[comm.first] = (comm.second == 'L' ? Left : Right);
        }

        board[0][0] = Body;
        body.emplace_back(0, 0);
    }

    bool step() {
        ++time;
        Point next = movePoint(body.front(), dir);
        
        if (next.first < 0 || size <= next.first ||
            next.second < 0 || size <= next.second ||
            board[next.first][next.second] == Body) {
            return false;
        }

        Cell nextCell = board[next.first][next.second];
        body.push_front(next);
        board[next.first][next.second] = Body;

        if (nextCell == Empty) {
            Point tail = body.back();
            body.pop_back();
            board[tail.first][tail.second] = Empty;
        }

        if (time < timeline.size() && timeline[time] != Undefined) {
            dir = (timeline[time] == Left ? turnLeft(dir) : turnRight(dir));
        }
        return true;
    }

    int getTime() {
        return time;
    }
};

int main() {
    int n;
    scanf("%d", &n);

    std::vector<Point> apples;
    int appleCount = 0;
    scanf("%d", &appleCount);
    for (int i = 0; i < appleCount; ++i) {
        int r, c;
        scanf("%d %d", &r, &c);
        apples.emplace_back(r-1, c-1);
    }

    std::vector<std::pair<int, char>> commands;
    int commCount = 0;
    scanf("%d", &commCount);
    for (int i = 0; i < commCount; ++i) {
        std::pair<int, char> comm;
        scanf("%d %c", &comm.first, &comm.second);
        commands.push_back(comm);
    }

    Game g(n, apples, commands);
    while (g.step());
    printf("%d", g.getTime());

    return 0;
}
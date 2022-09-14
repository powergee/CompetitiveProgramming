#include <iostream>

enum Direction {
    North, West, East, South
};

Direction getLeft(Direction dir) {
    switch (dir)
    {
    case North:
        return West;
    case West:
        return South;
    case East:
        return North;
    case South:
        return East;
    }
    return North;
}

Direction getRight(Direction dir) {
    switch (dir)
    {
    case North:
        return East;
    case West:
        return North;
    case East:
        return South;
    case South:
        return West;
    }
    return North;
}

class Robot {
private:
    int num;
    int x, y;
    Direction dir;

public:
    Robot(int num, int x, int y, Direction dir) {
        this->num = num;
        this->x = x;
        this->y = y;
        this->dir = dir;
    }

    void turnLeft() {
        dir = getLeft(dir);
    }

    void turnRight() {
        dir = getRight(dir);
    }

    void goForward() {
        switch (dir)
        {
        case North:
            ++y;
            break;
        case West:
            --x;
            break;
        case East:
            ++x;
            break;
        case South:
            --y;
            break;
        }
    }

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    int getNumber() {
        return num;
    }
};

class Map {
private: 
    int robotCount;
    int width, height;
    Robot* map[101][101];
    Robot* robots[101];

public:
    Map(int width, int height) {
        robotCount = 0;
        this->width = width;
        this->height = height;

        std::fill(&map[0][0], &map[0][0] + sizeof(map) / sizeof(Robot*), nullptr);
        std::fill(robots, robots + sizeof(robots) / sizeof(Robot*), nullptr);
    }

    void addRobot(int x, int y, char dir) {
        Direction dirEnum;
        switch (dir)
        {
        case 'N':
            dirEnum = North;
            break;
        case 'W':
            dirEnum = West;
            break;
        case 'E':
            dirEnum = East;
            break;
        case 'S':
            dirEnum = South;
            break;
        }
        Robot* robot = new Robot(++robotCount, x, y, dirEnum);
        map[x][y] = robot;
        robots[robotCount] = robot;
    }

    int executeCommand(int num, char kind, int count) {
        Robot* robot = robots[num];

        while (count--) {
            switch (kind)
            {
            case 'L':
                robot->turnLeft();
                break;

            case 'R':
                robot->turnRight();
                break;

            case 'F':
                map[robot->getX()][robot->getY()] = nullptr;
                robot->goForward();
                
                int nx = robot->getX();
                int ny = robot->getY();
                if (nx < 1 || nx > width || ny < 1 || ny > height) {
                    return -1;
                }
                if (map[nx][ny] != nullptr) {
                    return map[nx][ny]->getNumber();
                }

                map[nx][ny] = robot;
                break;
            }
        }

        return 0;
    }
};

int main() {
    int a, b, n, m;
    scanf("%d %d", &a, &b);
    scanf("%d %d", &n, &m);
    Map map(a, b);

    while (n--) {
        int x, y;
        char dir;
        scanf("%d %d %c", &x, &y, &dir);
        map.addRobot(x, y, dir);
    }

    while (m--) {
        int num, count;
        char kind;
        scanf("%d %c %d", &num, &kind, &count);
        int result = map.executeCommand(num, kind, count);

        if (result == -1) {
            printf("Robot %d crashes into the wall", num);
            return 0;
        } else if (result != 0) {
            printf("Robot %d crashes into robot %d", num, result);
            return 0;
        }
    }

    printf("OK");

    return 0;
}
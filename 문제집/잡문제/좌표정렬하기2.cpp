#include <iostream>
#include <algorithm>

class Point
{
private:
	int X, Y;
public:
    Point();
	Point(int x, int y);
	void WriteLine() const;
	bool operator < (const Point& p) const;
};

int main()
{
    Point* pArr;
    int count;
    scanf("%d", &count);
    pArr = new Point[count];

    for (int i = 0; i < count; ++i)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        Point p(x, y);
        pArr[i] = p;
    }

    std::sort(pArr, pArr + count);

    for (int i = 0; i < count; ++i)
    {
        pArr[i].WriteLine();
    }

    delete[] pArr;

	return 0;
}

Point::Point()
{
    X = 0;
    Y = 0;
}

Point::Point(int x, int y)
{
	X = x;
	Y = y;
}

void Point::WriteLine() const
{
	printf("%d %d\n", X, Y);
}

bool Point::operator<(const Point& p) const
{
	if (Y < p.Y)
		return true;
	else if (Y == p.Y)
		return X < p.X;
	else return false;
}
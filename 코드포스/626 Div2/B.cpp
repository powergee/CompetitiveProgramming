#include <iostream>
#include <algorithm>

typedef long long Long;

int n, m, k;
int a[40000], b[40000];

int SegLength_A(int start, int& end)
{
    int pos = start;
    while (pos + 1 < n && a[pos + 1])
        ++pos;

    int result = pos - start + 1;
    end = pos + 1;
    return result;
}

int SegLength_B(int start, int& end)
{
    int pos = start;
    while (pos + 1 < m && b[pos + 1])
        ++pos;

    int result = pos - start + 1;
    end = pos + 1;
    return result;
}

int SegCount_A(int width)
{
    int count = 0;
    for (int col = 0; col < n;)
    {
        if (a[col])
        {
            int segLen = SegLength_A(col, col);
            if (segLen >= width)
                count += (segLen - width + 1);
        }
        else ++col;
    }

    return count;
}

int SegCount_B(int height)
{
    int count = 0;
    for (int row = 0; row < m;)
    {
        if (b[row])
        {
            int segLen = SegLength_B(row, row);
            if (segLen >= height)
                count += (segLen - height + 1);
        }
        else ++row;
    }

    return count;
}

Long Count(int width, int height)
{
    return (Long)SegCount_A(width) * SegCount_B(height);
}

int main()
{
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    for (int i = 0; i < m; ++i)
        scanf("%d", b + i);

    Long count = 0;
    for (int w = 1; w <= std::min(n, k); ++w)
    {
        if (k % w == 0)
        {
            int h = k / w;
            count += Count(w, h);
        }
    }

    printf("%lld", count);

    return 0;
}
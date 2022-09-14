#include <iostream>
#include <algorithm>

char str[1000001];

int main()
{
    int n, m;
    scanf("%d%d%s", &n, &m, str);

    int i = 0;
    int length = -1;
    int count = 0;
    while (i < m)
    {
        if (length == -1)
        {
            for (; i < m; ++i)
            {
                if (str[i] == 'I')
                {
                    length = 0;
                    break;
                }
            }
        }
        else
        {
            if (i + 2 >= m || !(str[i + 1] == 'O' && str[i + 2] == 'I'))
            {
                count += std::max(0, length - n + 1);
                length = -1;
                ++i;
            }
            else
            {
                i += 2;
                ++length;
            }
        }
    }

    printf("%d", count);

    return 0;
}
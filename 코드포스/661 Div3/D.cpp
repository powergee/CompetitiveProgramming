#include <iostream>
#include <vector>

char str[200001];
int belong[200001];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);
        scanf("%s", str);

        std::vector<int> count[2];
        int result = 1;

        if (str[0] == '0')
            count[0].push_back(0);
        else
            count[1].push_back(0);
        belong[0] = 0;

        for (int i = 1; i < n; ++i)
        {
            if (str[i] == '0')
            {
                if (!count[1].empty())
                {
                    int pos = count[1].back();
                    count[1].pop_back();
                    count[0].push_back(pos);
                    belong[i] = pos;
                }
                else
                {
                    count[0].push_back(result);
                    belong[i] = result;
                    ++result;
                }
            }
            else
            {
                if (!count[0].empty())
                {
                    int pos = count[0].back();
                    count[0].pop_back();
                    count[1].push_back(pos);
                    belong[i] = pos;
                }
                else
                {
                    count[1].push_back(result);
                    belong[i] = result;
                    ++result;
                }
            }
        }

        printf("%d\n", result);
        for (int i = 0; i < n; ++i)
            printf("%d ", belong[i]+1);
        printf("\n");
    }

    return 0;
}
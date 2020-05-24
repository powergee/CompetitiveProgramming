#include <iostream>
#include <vector>
using namespace std;

typedef pair<int, int> Date;
typedef pair<Date, Date> FlTerm;

int N;
vector<FlTerm> flowers;

int main()
{
    scanf("%d", &N);

    for (int i = 0; i < N; ++i)
    {
        int sm, sd, em, ed;
        scanf("%d %d %d %d", &sm, &sd, &em, &ed);

        flowers.push_back(FlTerm(Date(sm, sd), Date(em, ed)));
    }

    Date start(3, 1), end(11, 30);
    Date currentEnd;
    int flCount;
    FlTerm toPlant(Date(3, 1), Date(-1, -1));
    for (auto term : flowers)
    {
        if (term.first <= start && toPlant.second < term.second)
        {
            toPlant = term;
        }
    }

    if (toPlant.second.first == -1)
    {
        printf("0");
    }
    else
    {
        flCount = 1;
        currentEnd = toPlant.second;
        while (currentEnd <= end)
        {
            for (auto term : flowers)
            {
                if (term.first <= currentEnd && toPlant.second < term.second)
                {
                    toPlant = term;
                }
            }

            if (toPlant.second == currentEnd)
            {
                printf("0");
                return 0;
            }
            ++flCount;
            currentEnd = toPlant.second;
        }

        printf("%d", flCount);
    }

    return 0;
}
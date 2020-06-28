#include <iostream>
#include <set>
#include <algorithm>

struct Book
{
    int t, a, b;

    bool operator<(const Book& other) const
    {
        return t > other.t;
    }
};

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);

    std::multiset<Book> bookSet[3];
    Book sum = {0, 0, 0};
    for (int i = 0; i < n; ++i)
    {
        int t, a, b;
        scanf("%d %d %d", &t, &a, &b);

        if (a != 0 || b != 0)
        {
            sum.a += a;
            sum.b += b;
            sum.t += t;
            if (a == 1 && b == 0)
                bookSet[0].insert({t, 1, 0});
            else if (a == 0 && b == 1)
                bookSet[1].insert({t, 0, 1});
            else
                bookSet[2].insert({t, 1, 1});
        }
    }

    /*printf("[0]\n");
    for (Book b : bookSet[0])
        printf("%d %d %d\n", b.t, b.a, b.b);
    printf("\n");
    printf("[1]\n");
    for (Book b : bookSet[1])
        printf("%d %d %d\n", b.t, b.a, b.b);
    printf("\n");
    printf("[2]\n");
    for (Book b : bookSet[2])
        printf("%d %d %d\n", b.t, b.a, b.b);
    printf("\n");*/

    int freeA = sum.a - k;
    int freeB = sum.b - k;

    if (freeA < 0 || freeB < 0)
        printf("-1");
    else
    {
        while (freeA > 0 && freeB > 0 && (!bookSet[0].empty() && !bookSet[1].empty() && !bookSet[2].empty()))
        {
            //printf("freeA=%d, freeB=%d\n", freeA, freeB);
            auto aDump = bookSet[0].begin();
            auto bDump = bookSet[1].begin();
            auto dDump = bookSet[2].begin();

            if (aDump->t + bDump->t > dDump->t)
            {
                //printf("Delete: {%d, %d, %d}, {%d, %d, %d}\n", aDump->t, aDump->a, aDump->b, bDump->t, bDump->a, bDump->b);
                bookSet[0].erase(aDump);
                bookSet[1].erase(bDump);
            }
            else
            {
                //printf("Delete: {%d, %d, %d}\n", dDump->t, dDump->a, dDump->b);
                bookSet[2].erase(dDump);
            }
            --freeA;
            --freeB;
            //printf("freeA=%d, freeB=%d\n", freeA, freeB);
        }

        while (freeA > 0 && !bookSet[0].empty())
        {
            //printf("freeA=%d, freeB=%d\n", freeA, freeB);
            auto dump = bookSet[0].begin();
            //printf("Delete: {%d, %d, %d}\n", dump->t, dump->a, dump->b);
            bookSet[0].erase(dump);
            --freeA;
            //printf("freeA=%d, freeB=%d\n", freeA, freeB);
        }

        while (freeB > 0 && !bookSet[1].empty())
        {
            //printf("freeA=%d, freeB=%d\n", freeA, freeB);
            auto dump = bookSet[1].begin();
            //printf("Delete: {%d, %d, %d}\n", dump->t, dump->a, dump->b);
            bookSet[1].erase(dump);
            --freeB;
            //printf("freeA=%d, freeB=%d\n", freeA, freeB);
        }

        while (freeA > 0 && freeB > 0 && !bookSet[2].empty())
        {
            //printf("freeA=%d, freeB=%d\n", freeA, freeB);
            auto dump = bookSet[2].begin();
            //printf("Delete: {%d, %d, %d}\n", dump->t, dump->a, dump->b);
            bookSet[2].erase(dump);
            --freeA;
            --freeB;
            //printf("freeA=%d, freeB=%d\n", freeA, freeB);
        }

        long long answer = 0;

        for (int i = 0; i < 3; ++i)
            for (auto b : bookSet[i])
                answer += b.t;
        
        std::cout << answer;
    }
}
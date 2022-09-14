#include <iostream>
#include <algorithm>

int k;
char parSeq[9];
int numSeq[10];
bool appeared[10];

int maxSeq[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int minSeq[10] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};

// seq의 길이는 k+1이다.
bool RightIsBigger(int* seq1, int* seq2)
{
    for (int i = 0; i < k+1; ++i)
    {
        if (seq1[i] > seq2[i])
            return false;

        if (seq1[i] < seq2[i])
            return true;
    }
    return false;
}

bool InequalityHolds(int numIndex)
{
    if (numIndex == 0)
        return true;
    
    char par = parSeq[numIndex - 1];

    if (par == '<')
        return numSeq[numIndex - 1] < numSeq[numIndex];
    else
        return numSeq[numIndex - 1] > numSeq[numIndex];
}

void FindCases(int start)
{
    if (start >= k+1)
    {
        if (RightIsBigger(maxSeq, numSeq))
            std::copy(numSeq, numSeq + k + 1, maxSeq);
        if (RightIsBigger(numSeq, minSeq))
            std::copy(numSeq, numSeq + k + 1, minSeq);
        
        return;
    }

    // 앞에서 이어짐...

    for (int i = 0; i <= 9; ++i)
    {
        if (appeared[i])
            continue;
        
        numSeq[start] = i;
        if (InequalityHolds(start))
        {
            appeared[i] = true;
            FindCases(start + 1);
            appeared[i] = false;
        }
    }
}

int main()
{
    scanf("%d", &k);

    for (int i = 0; i < k; ++i)
    {
        char input[2];
        scanf("%s", input);
        parSeq[i] = input[0];
    }

    FindCases(0);
    
    for (int i = 0; i < k+1; ++i)
        printf("%d", maxSeq[i]);
    printf("\n");

    for (int i = 0; i < k+1; ++i)
        printf("%d", minSeq[i]);

    return 0;
}
#include <iostream>
#include <vector>

std::vector<char> arr;
std::vector<char> temp;

bool Compare(char a, char b)
{
    printf("? %c %c\n", a, b);
    fflush(stdout);
    char ans;
    scanf(" %c", &ans);
    return ans == '<';
}

void MergeSort(int left, int right)
{
    if (left == right)
        return;
    
    int length = right - left + 1;
    int med = (left + right) / 2;
    MergeSort(left, med);
    MergeSort(med + 1, right);

    int i = left, j = med + 1, pos = 0;
    while (pos < length)
    {
        if (Compare(arr[i], arr[j]))
            temp[pos++] = arr[i++];
        else
            temp[pos++] = arr[j++];

        if (i > med)
            while (j <= right)
                temp[pos++] = arr[j++];
                
        else if (j > right)
            while (i <= med)
                temp[pos++] = arr[i++];
    }

    for (int k = 0; k < length; ++k)
        arr[left + k] = temp[k];
}

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);

    if (n != 5)
    {
        arr.resize(n);
        temp.resize(n);
        for (int i = 0; i < n; ++i)
            arr[i] = 'A' + i;
        MergeSort(0, n - 1);
        for (char ch : arr)
            printf("%c", ch);
        printf("\n");
    }
    else
    {
        char sub[2][2];
        if (Compare('A', 'B'))
            sub[0][0] = 'A', sub[0][1] = 'B';
        else
            sub[0][0] = 'B', sub[0][1] = 'A';

        if (Compare('C', 'D'))
            sub[1][0] = 'C', sub[1][1] = 'D';
        else
            sub[1][0] = 'D', sub[1][1] = 'C';

        if (Compare(sub[0][1], sub[1][1]))
        {
            // sub[0][0] < sub[0][1] < sub[1][1]
            if (Compare(sub[0][1], 'E'))
            {
                if (Compare(sub[1][1], 'E'))
                {
                    // sub[0][0] < sub[0][1] < sub[1][1] < E
                    if (Compare(sub[0][0], sub[1][0]))
                    {
                        if (Compare(sub[0][1], sub[1][0]))
                            printf("%c%c%c%c%c", sub[0][0], sub[0][1], sub[1][0], sub[1][1], 'E');
                        else
                            printf("%c%c%c%c%c", sub[0][0], sub[1][0], sub[0][1], sub[1][1], 'E');
                    }
                    else
                    {
                        printf("%c%c%c%c%c", sub[1][0], sub[0][0], sub[0][1], sub[1][1], 'E');
                    }
                }
                else
                {
                    // sub[0][0] < sub[0][1] < E < sub[1][1]
                    if (Compare(sub[0][1], sub[1][0]))
                    {

                    }
                    else
                    {
                        
                    }
                }
            }
            else
            {
                if (Compare(sub[0][0], 'E'))
                {
                    // sub[0][0] < E < sub[0][1] < sub[1][1]
                }
                else
                {
                    // E < sub[0][0] < sub[0][1] < sub[1][1]
                }
            }
        }
        else
        {
            // sub[1][0] < sub[1][1] < sub[0][1]
            if (Compare(sub[1][1], 'E'))
            {
                if (Compare(sub[0][1], 'E'))
                {
                    // sub[1][0] < sub[1][1] < sub[0][1] < E
                }
                else
                {
                    // sub[1][0] < sub[1][1] < E < sub[0][1]
                }
            }
            else
            {
                if (Compare(sub[1][0], 'E'))
                {
                    // sub[1][0] < E < sub[1][1] < sub[0][1]
                }
                else
                {
                    // E < sub[1][0] < sub[1][1] < sub[0][1]
                }
            }
        }
    }

    return 0;
}
#include <iostream>
#include <cstring>

char poem[100001];
int arr[100000];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        scanf("%s", poem);
        int length = strlen(poem);

        for (int i = 0; i < length; ++i)
            arr[i] = poem[i];
        
        int arbitrary = 'z' + 1;
        int answer = 0;
        for (int i = 0; i < length; ++i)
        {
            if (i+1 < length && arr[i] == arr[i+1])
            {
                arr[i+1] = arbitrary++;
                ++answer;
            }

            if (i+2 < length && arr[i] == arr[i+2])
            {
                arr[i+2] = arbitrary++;
                ++answer;
            }
        }

        printf("%d\n", answer);
    }

    return 0;
}
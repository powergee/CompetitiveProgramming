#include <iostream>
#include <algorithm>

int main()
{
    int n;
    int arr[11];
    char op[10];
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
        scanf("%d", arr + i);
    
    int add, sub, mul, div;
    scanf("%d%d%d%d", &add, &sub, &mul, &div);
    std::fill(op, op + add, '+');
    std::fill(op + add, op + add + sub, '-');
    std::fill(op + add + sub, op + add + sub + mul, '*');
    std::fill(op + add + sub + mul, op + add + sub + mul + div, '/');
    std::sort(op, op + n - 1);
    
    int min = 1e9, max = -1e9;
    do {
        int result = arr[0];
        for (int i = 0; i < n - 1; ++i)
        {
            switch (op[i])
            {
            case '+':
                result += arr[i + 1];
                break;
            case '-':
                result -= arr[i + 1];
                break;
            case '*':
                result *= arr[i + 1];
                break;
            case '/':
                result /= arr[i + 1];
            }
        }

        min = std::min(min, result);
        max = std::max(max, result);
    } while (std::next_permutation(op, op + n - 1));
    printf("%d\n%d", max, min);

    return 0;
}
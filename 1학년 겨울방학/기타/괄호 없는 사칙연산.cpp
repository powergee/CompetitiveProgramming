#include <iostream>

int nums[3];
char ops[2];
int subResults[2];
int results[2];

int Calc(int n1, char op, int n2)
{
    switch (op)
    {
    case '+':
        return n1 + n2;
        break;

    case '-':
        return n1 - n2;
        break;

    case '*':
        return n1 * n2;
        break;

    case '/':
        return n1 / n2;
        break;
    
    default:
        return 0;
        break;
    }
}

int main()
{
    scanf("%d", nums);
    scanf(" %c ", ops);
    scanf("%d", nums + 1);
    scanf(" %c ", ops + 1);
    scanf("%d", nums + 2);

    subResults[0] = Calc(nums[0], ops[0], nums[1]);
    results[0] = Calc(subResults[0], ops[1], nums[2]);

    subResults[1] = Calc(nums[1], ops[1], nums[2]);
    results[1] = Calc(nums[0], ops[0], subResults[1]);

    if (results[0] <= results[1])
        printf("%d\n%d", results[0], results[1]);

    if (results[1] < results[0])
        printf("%d\n%d", results[1], results[0]);

    return 0;
}
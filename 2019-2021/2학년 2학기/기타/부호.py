for t in range(0, 3):
    n = int(input())
    sum = 0
    for i in range(0, n):
        val = int(input())
        sum += val
    if sum == 0:
        print(0)
    elif sum > 0:
        print('+')
    else:
        print('-')
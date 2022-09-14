def printAll(n: int, m: int, start: int, array: list):
    if len(array) == m:
        print(" ".join(map(str, array)))
    elif start <= n:
        array.append(start)
        printAll(n, m, start, array)
        array.pop()
        printAll(n, m, start+1, array)

n, m = list(map(int, input().split()))
printAll(n, m, 1, [])
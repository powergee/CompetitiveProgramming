dp = [[-1 for _ in range(101)] for _ in range(101)]

def CalcComb(n, m):
    if n < m:
        return 0
    if n == 0 or m == 0:
        return 1

    if dp[n][m] != -1:
        return dp[n][m]
    
    dp[n][m] = CalcComb(n-1, m-1) + CalcComb(n-1, m)
    return dp[n][m]

print(CalcComb(*map(int, input().split(' '))))
a, b, c = list(map(int, input().split()))
d = int(input())
total = c + b*60 + a*60*60 + d
print(total//3600%24, total//60%60, total%60)

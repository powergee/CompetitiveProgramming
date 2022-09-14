day = int(input())
arr = list(map(int, input().split()))
print(len(list(filter(lambda v : v == day, arr))))
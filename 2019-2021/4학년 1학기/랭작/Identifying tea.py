actual = int(input())
answer = list(map(int, input().split()))
print(len(list(filter(lambda v : v == actual, answer))))
truth = list(map(int, input().split()))
truth = truth[0] * truth[1]

news = list(map(int, input().split()))
for n in news:
    print(n-truth, end=" ")
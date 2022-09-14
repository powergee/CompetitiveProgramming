import sys
input = sys.stdin.readline

n, p = list(map(int, input().split()))

touching = [[] for _ in range(7)]
count = 0
for _ in range(n):
    line, fret = list(map(int, input().split()))
    while len(touching[line]) > 0 and touching[line][-1] > fret:
        touching[line].pop()
        count += 1
    if len(touching[line]) == 0 or touching[line][-1] < fret:
        touching[line].append(fret)
        count += 1
print(count)
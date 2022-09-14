import sys
input = sys.stdin.readline

n, g, k = list(map(int, input().split(" ")))

persistent, removable = [], []
for i in range(n):
    s, l, o = list(map(int, input().split(" ")))
    if o == 1:
        removable.append([s, l])
    else:
        persistent.append([s, l])

def is_possible(t):
    sum = 0
    for s, l in persistent:
        sum += s * max(1, t-l)
        if sum > g:
            return False
    
    cands = []
    for s, l in removable:
        cands.append(s * max(1, t-l))
    cands.sort()
    if k < len(cands):
        for i in range(len(cands)-k):
            sum += cands[i]
            if sum > g:
                return False
    
    return True


left = 0; right = int(1e18)
while left+1 < right:
    mid = (left+right)//2
    if is_possible(mid):
        left = mid
    else:
        right = mid

if is_possible(right):
    print(right)
else:
    print(left)
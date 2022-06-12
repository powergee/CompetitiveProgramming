x, a, d, n = list(map(int, input().split(" ")))

def find_lower_bound(target, first, diff, count):
    left = 0; right = count-1
    while left < right:
        mid = (left+right) // 2
        if target <= first + diff*mid:
            right = mid
        else:
            left = mid+1
    return first + diff*left

first = a
last = a + d*(n-1)

if d < 0:
    first, last = last, first
    d = -d

if x <= first:
    print(first-x)
elif last <= x:
    print(x-last)
else:
    c1 = find_lower_bound(x, first, d, n)
    c2 = c1 - d
    print(min(abs(c1-x), abs(c2-x)))
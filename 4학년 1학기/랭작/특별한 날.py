month = int(input())
day = int(input())
total = month*31 + day
pivot = 2*31 + 18

if total < pivot:
    print("Before")
elif pivot == total:
    print("Special")
else:
    print("After")
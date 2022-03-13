def to_seconds(triple):
    return triple[0]*3600 + triple[1]*60 + triple[2]

for i in range(3):
    arr = list(map(int, input().split()))
    diff = to_seconds(arr[3:]) - to_seconds(arr[:3])
    print(diff//3600, diff//60%60, diff%60)
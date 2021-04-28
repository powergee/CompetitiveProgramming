def count_all(arr, start, before, selected, count_dict):
    if len(arr) <= start and selected:
        if before in count_dict:
            count_dict[before] += 1
        else:
            count_dict[before] = 1
    elif start < len(arr):
        before += arr[start]
        count_all(arr, start+1, before, True, count_dict)
        before -= arr[start]
        count_all(arr, start+1, before, selected, count_dict)

[n, s] = list(map(int, input().split(" ")))
arr = list(map(int, input().split(" ")))
count1 = {}; count2 = {}

if n == 1:
    count_all(arr, 0, 0, False, count1)
    if s in count1:
        print(count1[s])
    else:
        print(0)
else:
    count_all(arr[:len(arr)//2], 0, 0, False, count1)
    count_all(arr[len(arr)//2:], 0, 0, False, count2)
    result = 0

    for k in count1:
        if k == s:
            result += count1[k]
        spare = s-k
        if spare in count2:
            result += count1[k] * count2[spare]
    
    if s in count2:
        result += count2[s]
    
    print(result)
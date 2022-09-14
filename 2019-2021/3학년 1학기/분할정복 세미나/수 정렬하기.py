import sys
input = sys.stdin.readline

def merge_array(a, b):
    result = []
    i = 0; j = 0

    while i < len(a) and j < len(b):
        if a[i] < b[j]:
            result.append(a[i])
            i += 1
        else:
            result.append(b[j])
            j += 1
        
    while i < len(a):
        result.append(a[i])
        i += 1

    while j < len(b):
        result.append(b[j])
        j += 1
    
    return result

def merge_sort(arr):
    if len(arr) <= 1:
        return arr
    
    left = merge_sort(arr[:len(arr)//2])
    right = merge_sort(arr[len(arr)//2:])
    return merge_array(left, right)

n = int(input())
arr = []
for i in range(0, n):
    arr.append(int(input()))

print("\n".join(map(str, merge_sort(arr))))
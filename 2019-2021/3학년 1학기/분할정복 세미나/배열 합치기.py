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

n, m = list(map(int, input().split(" ")))
a = list(map(int, input().split(" ")))
b = list(map(int, input().split(" ")))
print(" ".join(map(str, merge_array(a, b))))
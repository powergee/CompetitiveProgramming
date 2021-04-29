import sys
input = sys.stdin.readline

def count_add(nums, prev_max):
    if len(nums) == 0:
        return 0

    max_val = max(nums)
    min_val = min(nums)
    max_idx = nums.index(max_val)

    if max_val == min_val:
        return prev_max - max_val
    
    result = count_add(nums[:max_idx], max_val)
    result += count_add(nums[max_idx+1:], max_val)
    result += prev_max - max_val
    return result


n = int(input())
nums = []
for i in range(0, n):
    nums.append(int(input()))

print(count_add(nums, max(nums)))
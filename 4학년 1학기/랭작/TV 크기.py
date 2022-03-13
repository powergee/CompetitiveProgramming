import math
x, h, w = list(map(int, input().split()))
r = x / math.sqrt(w*w + h*h)
print(math.floor(h*r), math.floor(w*r))
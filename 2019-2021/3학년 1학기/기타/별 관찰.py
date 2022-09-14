day = "Saturday, Sunday, Monday, Tuesday, Wednesday, Thursday, Friday".split(", ")

def get_minutes():
    line = input()
    tokens = line.split(":")
    return int(tokens[0]) * 60 + int(tokens[1])

s1 = get_minutes()
s2 = get_minutes()
t1 = get_minutes()
t2 = get_minutes()

cand = []

for i in range(1, 2000):
    if (s1-s2+i*t1) % t2 == 0 and s1-s2+i*t1 >= 0:
        cand.append(s1+i*t1)
        break

for i in range(1, 2000):
    if (s2-s1+i*t2) % t1 == 0 and s2-s1+i*t2 >= 0:
        cand.append(s2+i*t2)
        break

if len(cand) == 0:
    print("Never")
else:
    time = min(cand)
    print(day[(time // 1440) % len(day)])
    time %= 1440
    print(f"{time // 60:02d}:{time % 60:02d}")
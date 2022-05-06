T = int(input())

count = 0
for _ in range(T):
    line = input()
    st = []
    for ch in line:
        if len(st) > 0 and st[-1] == ch:
            st.pop()
        else:
            st.append(ch)
    if len(st) == 0:
        count += 1
print(count)

n = int(input())

row1 = ""
row2 = ""
for i in range(0, n):
    if i % 2 == 0:
        row1 += "*"
        row2 += " "
    else:
        row1 += " "
        row2 += "*"
for i in range(0, n):
    print(row1)
    print(row2)
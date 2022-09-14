code = "9780921418" + input() + input() + input()
coeff = [1, 3]
total = 0
for i in range(len(code)):
    total += int(code[i]) * coeff[i%2]
print("The 1-3-sum is", total)
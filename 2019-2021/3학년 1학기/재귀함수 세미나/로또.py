def find_comb(numbers, start, selected):
    if len(selected) == 6:
        print(" ".join(selected))
    elif start < len(numbers):
        selected.append(numbers[start])
        find_comb(numbers, start+1, selected)
        selected.pop()
        find_comb(numbers, start+1, selected)

while True:
    line = input()
    if line == "0":
        break
    tokens = line.split(" ")
    numbers = tokens[1:]
    find_comb(numbers, 0, [])
    print()
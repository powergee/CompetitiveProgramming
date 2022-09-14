def get_length(compressed, start):
    length = 0
    i = start
    while i < len(compressed):
        if compressed[i] == ")":
            break
        elif i+1 < len(compressed) and compressed[i+1] == "(":
            coeff = int(compressed[i])
            (sub_length, sub_end) = get_length(compressed, i+2)
            length += coeff * sub_length
            i = sub_end
        else:
            length += 1
        i += 1
    return (length, i)

print(get_length(input(), 0)[0])
def find_pos(size, start_num, row, col):
    if size == 2:
        return start_num + row*2 + col

    elif (row < size//2) and (col < size//2):
        return find_pos(size//2, start_num, row, col)

    elif (row < size//2) and (col >= size//2):
        return find_pos(size//2, start_num + (size//2)**2, row, col-(size//2))
    
    elif (row >= size//2) and (col < size//2):
        return find_pos(size//2, start_num + 2*(size//2)**2, row-(size//2), col)

    elif (row >= size//2) and (col >= size//2):
        return find_pos(size//2, start_num + 3*(size//2)**2, row-(size//2), col-(size//2))

[N, r, c] = list(map(int, input().split(" ")))
print(find_pos(2**N, 0, r, c))
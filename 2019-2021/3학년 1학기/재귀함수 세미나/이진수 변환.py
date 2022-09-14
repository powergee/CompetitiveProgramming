def print_binary(num):
    if num < 2:
        print(num, end="")
    else:
        print_binary(num // 2)
        print(num % 2, end="")

print_binary(int(input()))
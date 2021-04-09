def print_hanoi(disks, src, aux, dst):
    if disks == 1:
        print(src, dst)
    else:
        print_hanoi(disks - 1, src, dst, aux)
        print(src, dst)
        print_hanoi(disks - 1, aux, src, dst)

disks = int(input())
print(2 ** disks - 1)
print_hanoi(disks, 1, 2, 3)
val = input()

if val[0] != '0':
    print(val)
elif val[1] != 'x':
    print(int(val, 8))
else:
    print(int(val, 0))
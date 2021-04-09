print("[n, m] = list(map(int, input().split(' ')))")

for m in range(1, 9):
    if m == 1:
        print("if m == 1:")
    else:
        print(f"elif m == {m}:")
    
    var = 'a'
    for i in range(0, m):
        if var == 'a':
            print("\tfor a in range(1, n+1):")
        else:
            print("\t" * (i+1) + f"for {var} in range({chr(ord(var)-1)}+1, n+1):")
        var = chr(ord(var)+1)
    print("\t" * (m+1) + f"print({', '.join(list(map(chr, range(ord('a'), ord('a')+m))))})")

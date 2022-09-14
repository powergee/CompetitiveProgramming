sides = list(map(int, input().split()))
sides.sort()

equilateral = sides[0] == sides[1] and sides[1] == sides[2]
right = sides[0]**2 + sides[1]**2 == sides[2]**2

if right:
    print(1)
elif equilateral:
    print(2)
else:
    print(0)
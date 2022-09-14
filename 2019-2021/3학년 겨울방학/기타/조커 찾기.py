import sys
input = sys.stdin.readline

n = int(input())
cards = list(range(0, 27))

for i in range(n):
    seq = list(map(int, input().split()))
    left = cards[:13]
    right = cards[13:]
    new_cards = []
    for j in range(len(seq)):
        if j % 2 == 0:
            new_cards += right[:seq[j]]
            right = right[seq[j]:]
        else:
            new_cards += left[:seq[j]]
            left = left[seq[j]:]
    cards = new_cards

print(cards.index(0)+1)
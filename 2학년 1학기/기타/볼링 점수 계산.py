pin = [-1] * 21

def setScore(roll, ch, isLastFrame):
    if ch == 'S':
        pin[roll] = 10
        if isLastFrame:
            roll += 1
        else:
            pin[roll + 1] = -1
            roll += 2

    
    elif ch == 'P':
        pin[roll] = 10 - pin[roll - 1]
        roll += 1
    
    elif ch == '-':
        pin[roll] = 0
        roll += 1
    
    else:
        pin[roll] = int(ch)
        roll += 1

    return roll

def getNextRolls(start, count):
    sum = 0
    found = 0

    for i in range(start, len(pin)):
        if pin[i] != -1:
            found += 1
            sum += pin[i]
        
        if found == count:
            return sum
    
    return -1

# frame 번호는 1부터 시작
def getScore(frame):
    if frame < 1:
        return 0

    elif frame == 10:
        sum = 0
        for i in range(18, 21):
            if pin[i] != -1:
                sum += pin[i]
        
        return sum + getScore(frame - 1)

    else:
        pin1st = pin[frame * 2 - 2]
        pin2nd = pin[frame * 2 - 1]
        
        if pin2nd == -1:
            pin2nd = 0

        if pin1st + pin2nd < 10:
            return pin1st + pin2nd + getScore(frame - 1)

        elif pin1st == 10:
            bonus = getNextRolls(frame * 2, 2)
            return 10 + bonus + getScore(frame - 1)
        
        else:
            bonus = getNextRolls(frame * 2, 1)
            return 10 + bonus + getScore(frame - 1)

scoreStr = input()
roll = 0
strIndex = 0

while roll < 18:
    ch = scoreStr[strIndex]
    roll = setScore(roll, ch, False)
    strIndex += 1

while strIndex < len(scoreStr):
    roll = setScore(roll, scoreStr[strIndex], True)
    strIndex += 1

print(getScore(10))
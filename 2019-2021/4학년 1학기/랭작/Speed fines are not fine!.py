limit = int(input())
speed = int(input())

if speed <= limit:
    print("Congratulations, you are within the speed limit!")
elif speed <= limit+20:
    print("You are speeding and your fine is $100.")
elif speed <= limit+30:
    print("You are speeding and your fine is $270.")
else:
    print("You are speeding and your fine is $500.")
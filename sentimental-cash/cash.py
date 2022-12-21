from cs50 import get_float


change = float
num = False

while True:
    change = get_float('HOW MANY CENTS: ')
    num = False
    if change > 0:
        break
    else:
        num = True


change = round(change * 100)

c = 0

    #quaters
quaters = 0
while change >= 25:

    change = change - 25
    quaters += 1
    c += 1


#dime
dime = 0
while change >= 10:

    change = change - 10
    dime += 1
    c += 1


    #nickels
nickels = 0
while change >= 5:

    change = change - 5
    nickels += 1
    c += 1


    #pennies
pennies = 0
while change >= 1:

    change = change - 1
    pennies += 1
    c += 1

amount = pennies + dime + quaters + nickels
print("change:", amount)









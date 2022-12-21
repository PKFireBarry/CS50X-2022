import random

'''think of a number between 1 and 100 the computer will try to guess that number'''

def guess(x):
    random_number = random.randint(1, x)
    guess = 0
    while guess != random_number:
        guess = int(input(f"What is the number between 1 and {x}:  "))
        if guess < random_number:
            print('too low')
        elif guess > random_number:
            print('too high')
    print('correct guess')


def computer_guess(x):
    low = 1
    high = x
    userinput = ''
    while userinput != 'c':
        guess = random.randint(low, high)
        userinput = input (f"is {guess} too high (h), too low (l), or correct (c)")
        if userinput == 'h':
            high = guess - 1
        elif userinput == 'l':
            low = guess + 1
    print(f'the number is {guess}. computers are smart!')

computer_guess(100)

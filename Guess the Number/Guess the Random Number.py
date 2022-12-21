import random
'''the computer will pick a number and you need to guess'''
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



guess(10)

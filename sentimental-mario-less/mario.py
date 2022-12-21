# TODO
import sys

def main():

    block = get_blocks()

    for i in range(0, block, 1):

        print((block - 1 - i) * " ", end="")
        print((i + 1)* "#")


def get_blocks():

    n = input("how tall is the stack: ")
    p = n
    try:
        while n.isdigit():
            p = int(float(n))
            if p > 0 and p <= 8:

                return p
            else:
                print("Invalid block size")
                break

    except: TypeError
    p = input()

    return int(p)




main()
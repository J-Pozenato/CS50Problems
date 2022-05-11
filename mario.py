# TODO
from cs50 import get_int

valid = False

#  loops until the user inputs a valid value for the height
while valid == False :
    height = get_int("Height: ")
    if height > 0 and height < 9:
        valid = True

#  create the pyramid
for i in range(1, height + 1):
    print(' ' * (height - i) + '#' * i + "  " + '#' * i)




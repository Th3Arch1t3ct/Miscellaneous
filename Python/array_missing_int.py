#!/usr/bin/env python3

# How do you find the missing number in a given integer array of 1 to 100?

import random

somearray = [None]* 100

missing = random.randint(1,101)
for i in range(100):
    if(i >= missing):
        somearray[i] = i + 1
    else:
        somearray[i] = i

for i in range(100):
    if i not in somearray:
        print("The missing number is: {}".format(i))
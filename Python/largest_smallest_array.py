#!/usr/bin/env python3

# How do you find the largest and smallest number in an unsorted integer array?

import random

somearray = [None]* 100

for i in range(100):
    somearray[i] = random.randint(1001)

for i in range(100):
    if i not in somearray:
        print("The missing number is: {}".format(i))
import random
import math


def monte_carlo(n):
    i = 0
    count = 0
    while i <= n:
        x = random.random()
        y = random.random()
        if math.pow(x, 2) + math.pow(y, 2) < 1:
            count += 1
        i += 1
    pi = 4*count/n
    print(pi)


monte_carlo(10000000)
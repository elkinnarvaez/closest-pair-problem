from sys import stdin
import random

MAXN = 500000

def multiple_cases():
    for N in range(10000, MAXN + 1, 10000):
        print(N)
        for _ in range(N):
            x = random.uniform(-400000, 400000)
            y = random.uniform(-400000, 400000)
            print(x, y)

def single_case():
    N = 300000
    print(N)
    for _ in range(N):
        x = random.uniform(-400000, 400000)
        y = random.uniform(-400000, 400000)
        print(x, y)

def main():
    multiple_cases()


if __name__ == '__main__':
    main()
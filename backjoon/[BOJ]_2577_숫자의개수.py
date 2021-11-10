import sys

num = 1
for _ in range(3):
    num *=  int(sys.stdin.readline().rstrip())
tmp = str(num)
for x in range(10):
    print(tmp.count(str(x)))
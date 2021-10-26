import sys


def Find(num):
    if node[num] == num:
        return num

    px = Find(node[num])
    node[num] = px
    return px


def union(num1, num2):
    node[Find(num2)] = Find(num1)



N, M = map(int, sys.stdin.readline().split())
node = [x for x in range(N+1)]

for _ in range(M):
    what, num1, num2 = map(int, sys.stdin.readline().split())
    if what:
        if Find(num1) == Find(num2):
            print('YES')
        else:
            print('NO')
    else:
        union(num1, num2)
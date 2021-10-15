"""
012_pm: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('012_pm_input.txt')

T = 10
for tc in range(1, T + 1):
    N = int(input())
    temp = [input().split() for _ in range(N)]
    tree = [0] * (N + 1)
    for x in range(len(temp)):
        try:
            tree[x+1] = int(temp[x][1])
        except:
            tree[x+1] = temp[x][1]
    po = N
    while po >= 0:
        if tree[po] == '+':
            tree[po] = int(tree[int(temp[po - 1][2])]) + int(tree[int(temp[po - 1][3])])
        elif tree[po] == '-':
            tree[po] = int(tree[int(temp[po - 1][2])]) - int(tree[int(temp[po - 1][3])])
        elif tree[po] == '*':
            tree[po] = int(tree[int(temp[po - 1][2])]) * int(tree[int(temp[po - 1][3])])
        elif tree[po] == '/':
            tree[po] = int(tree[int(temp[po - 1][2])]) / int(tree[int(temp[po - 1][3])])
        po -= 1

    print("#{} {}".format(tc, int(tree[1])))
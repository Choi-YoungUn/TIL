"""
002_box_change: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('002_box_change_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    nq = list(map(int,input().split()))
    box = [0] * nq[0]

    for x in range(1, nq[1] + 1):
        lr = list(map(int,input().split()))
        for y in range(lr[0] - 1, lr[1]):
            box[y] = x
    result =""
    for x in range(len(box)):
        result += str(box[x]) + ' '
    print("#%d %s" %(test_case , result[:-1]))

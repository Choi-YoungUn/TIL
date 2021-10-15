"""
004_ladder1: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('004_ladder1_input.txt')

T = 10
for test_case in range(1, T + 1):
    num = int(input())
    temp = []
    j = 0
    for x in range(100):
        temp.append(list(map(int,input().split())))
    # for y in range(99, -1, -1):
    #     if temp[99][y] == 2:
    #         j = y
    j = temp[99].index(2)
    end, i = 0, 99
    while end == 0:
        jj = j
        temp[i][j] = 2
        if j > 0 and temp[i][j - 1] == 1:
            j -= 1
        elif j < 99 and temp[i][j + 1] == 1:
            j += 1
        else:
            i -= 1
        if i == 0 and temp[i][j] == 1:
            end = j
    print("#{} {}".format(test_case ,end))
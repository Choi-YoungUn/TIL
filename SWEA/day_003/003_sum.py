"""
003_sum: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('003_sum_input.txt')

T = 10
for test_case in range(1, T + 1):
    sum_x = [0] * 100
    sum_y = [0] * 100
    sum_xy = 0
    sum_yx = 0
    num = int(input())
    temp = []
    for x in range(100):
        temp.append(list(map(int,input().split())))
    
    for i in range(100):
        for j in range(100):
            sum_x[i] += temp[i][j]
            sum_y[j] += temp[i][j]
            if i == j:
                sum_xy += temp[i][j]
            if (i+j) == 99:
                sum_yx += temp[i][j]
    result = 0
    x_sum = 0
    y_sum = 0
    for k in range(100):
        if x_sum < sum_x[k]:
            x_sum = sum_x[k]
        if y_sum < sum_y[k]:
            y_sum = sum_y[k]
    
    if result < x_sum:
        result = x_sum
    if result < y_sum:
        result = y_sum
    if result < sum_xy:
        result = sum_xy
    if result < sum_yx:
        result = sum_yx
    print("#%d %d" %(test_case , result))

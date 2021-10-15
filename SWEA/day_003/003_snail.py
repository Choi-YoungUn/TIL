"""
003_snail: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('003_snail_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    num = int(input())
    box_list = []
    for x in range(num):
        box_list.append([0] * num)
    i = 0
    j = 0
    lon = num
    number = 1
    col = True
    for x in range(1, num + num):

        for next in range(lon):
            if x % 2 != 0 :
                if col == True:
                    box_list[i][j] = number 
                    number += 1
                    j += 1
                else:
                    box_list[i][j] = number 
                    number += 1
                    j -= 1
            elif x % 2 == 0:
                if col == True:
                    box_list[i][j] = number 
                    number += 1
                    i += 1
                else:
                    box_list[i][j] = number 
                    number += 1
                    i -= 1
        else:
            tt = x % 4

            if tt == 1:
                i += 1
                j -= 1
            elif tt == 2:
                j -= 1
                i -= 1
            elif tt == 3:
                j += 1
                i -= 1
            elif tt == 0:
                i += 1
                j += 1

        if  x % 2 == 0:
            col = not(col)
        elif x % 2 != 0:
            lon -= 1
    print("#%d" %(test_case))
    for x in range(num):
        for y in range(num):
            print(box_list[x][y], end=' ')
        print('')


        # di = [0, 1, 0, -1]
        # dj = [1, 0, -1, 0]

        # N = 5
        # cnt = 1
        # i, j = 0, -1
        # k = 0
        # while cnt <= N*N:
        #     ni, nj = i + di[k], j + dj[k]
        #     if ni, nj가 유효하고 and a[ni][nj] == 0:
        #         a[ni][nj] = cnt
        #         cnt += 1
        #         i, j = ni, nj
        #     else:
        #         k = (k+1) %4
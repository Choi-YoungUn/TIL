"""
stocu: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('stocu_input.txt')

T = int(input())
for test_case in range(1, T +1):
    box = []
    for x in range(9):
        box.append(list(map(int,input().split())))

    result = 1
    for x in range(9):
        nums_x = [0] * 9
        nums_y = [0] * 9
        
        for y in range(9):
            nums_x[box[x][y]-1] += 1
            nums_y[box[y][x]-1] += 1
            if nums_x[box[x][y]-1] > 1 or nums_y[box[y][x]-1] > 1:
                result = 0

            if x % 3 == 0 and y % 3 == 0:
                nums_xy = [0] * 9
                for addx in range(3):
                    for addy in range(3):
                        nums_xy[box[x+addx][y+addy] -1] += 1
                        if nums_xy[box[x+addx][y+addy] -1] > 1:
                            result = 0
                            break

                    if result == 0:
                        break
            if result == 0:
                break
        if result == 0:
            break   
        
    print("#{} {}".format(test_case , result))
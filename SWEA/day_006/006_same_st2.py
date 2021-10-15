"""
006_same_st2: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('006_same_st2_input.txt')


for test_case in range(1, 11):
    T = int(input())
    box =[]
    for x in range(100):
        box.append(list(input()))

    for x in range(100):
        temp = []
        for y in range(100):
            temp.append(box[y][x])
        box.append(temp)

    result = 0
    for toto in range(100, -1 ,-1):
        for k in range(len(box)):
            for x in range(100 - toto + 1):
                for y in range(toto // 2):
                    if box[k][x + y] != box[k][x + toto - y -1]:
                        break
                else:
                    result = toto
                    break
        if result != 0:
            break

    print("#{} {}".format(test_case , result))
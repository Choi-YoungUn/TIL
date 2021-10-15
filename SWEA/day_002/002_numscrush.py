"""
002_numscrush: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('002_numscrush_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    num = int(input())
    two = 0
    three = 0
    five = 0
    seven = 0
    ele = 0
    while True:
        if num % 2 == 0:
            num = num / 2
            two += 1
        elif num % 3 == 0:
            num = num / 3
            three += 1
        elif num % 5 == 0:
            num = num / 5
            five += 1
        elif num % 7 == 0:
            num = num / 7
            seven += 1
        elif num % 11 == 0:
            num = num / 11
            ele += 1
        if num <= 1:
            break

    print("#%d %d %d %d %d %d" %(test_case , two, three, five, seven, ele))
"""
009_tonar: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('009_tonar_input.txt')

def game(num1, num2):
    global card_list
    if card_list[num1] == 1:
        if card_list[num2] == 2:
            return num2
        elif card_list[num2] == 3:
            return num1
        elif card_list[num2] == 1:
            return num1
    elif card_list[num1]== 2:
        if card_list[num2] == 3:
            return num2
        elif card_list[num2] == 1:
            return num1
        elif card_list[num2] == 2:
            return num1
    elif card_list[num1] == 3:
        if card_list[num2] == 1:
            return num2
        elif card_list[num2] == 2:
            return num1
        elif card_list[num2] == 3:
            return num1


def fight(start , end):
    if start + 1 == end:
        return game(start, end)
    elif start == end:
        return start
    else:
        return game(fight(start, (start + end) // 2), fight((start + end) // 2 + 1, end))

T = int(input())
for tc in range(1, T + 1):
    N =int(input())
    card_list = list(map(int, input().split()))
    print("#%d %d" %(tc, fight(0, len(card_list) - 1) + 1))
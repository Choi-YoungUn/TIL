"""
002_numcard: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('002_numcard_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    card_num = int(input())
    cards_temp = input()
    cards_count =[0] * 10
    cards = []
    for x in range(card_num):
        cards.append(int(cards_temp[x]))

    for x in range(card_num):
        cards_count[cards[x]] += 1

    maxx = 0
    max_in = 0

    for x in range(len(cards_count)):
        if maxx <= cards_count[x]:
            maxx = cards_count[x]
            max_in = x

    print("#%d %d %d" %(test_case , max_in, cards_count[max_in]))
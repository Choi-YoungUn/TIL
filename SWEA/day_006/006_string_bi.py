"""
006_string_bi: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('006_string_bi_input.txt')

def move(lists, char):
    for x in range(len(lists)-2, -1, -1):
        if char == lists[x]:
            return len(lists) - 1 - x
    return len(lists)

def check(total_st, check_st):
    to_move = 0
    ch_len = len(check_st)
    
    while to_move <= len(total_st) - len(check_st):
        ch_move = len(check_st) -1
        while ch_move >= 0:
            if total_st[to_move + ch_move] != check_st[ch_move]:
                move_to = move(check_st, total_st[to_move + ch_len - 1])
                break
            ch_move -= 1

        if ch_move == -1:
            return 1
        else:
            to_move += move_to
    return 0


T = int(input())
for test_case in range(1, T + 1):
    n = input()
    m = input()
    print("#{} {}".format(test_case ,check(m, n)))


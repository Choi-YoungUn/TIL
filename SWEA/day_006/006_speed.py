"""
006_speed: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('006_speed_input.txt')

def moves(lists, char):
    for i in range(len(lists) -2, -1, -1):
        if lists[i] == char:
            return len(lists) - 1 - i
    return len(lists)

def moor(total, patten):
    m = len(total)
    n = len(patten)
    i = 0
    counts = 0
    while i <= m - n:
        j = n - 1
        while j >= 0:
            if total[i + j] != patten[j]:
                move = moves(patten, total[i + n - 1])
                break
            j -= 1
        if j == -1:
            counts += 1
            i += n
        else:
            i += move
    return counts

T = int(input())
for test_case in range(1, T + 1):
    
    text, patten = map(str, input().split())
    result = len(text) - ((len(patten) - 1) * moor(text, patten))
    print("#{} {}".format(test_case ,result))
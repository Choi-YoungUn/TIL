"""
baby: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('baby_input.txt')


def baby(num, card_list):
    if card_list[num] == 3:
        return True
    for x in range(8):
        if card_list[x] != 0 and  card_list[x+1] != 0 and card_list[x+2] != 0 :
            return True
    return False


T = int(input().strip())
for tc in range(1, T + 1):
    box = list(input().strip().split())
    A = [0] * 10
    B = [0] * 10
    result = 0
    for x in range(0,len(box),2):
        A[int(box[x])] += 1
        
        if len(A) >=3 :
            if baby(int(box[x]), A) :
                result = 1
                break
        B[int(box[x+1])] += 1
        if len(B) >=3 :
            if baby(int(box[x+1]),B):
                result = 2
                break
   
    print('#{} {}'.format(tc, result))
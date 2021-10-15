"""
binary2: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('binary2_input.txt')

T = int(input().strip())
for tc in range(1, T + 1):
    N = float(input().strip())
    result = ''
    up_num = -1
    while  N > 0:
        if N >= 2 ** up_num:
            result += '1'
            N -= 2 ** up_num
        else:
            result += '0'
        up_num -= 1
        if len(result)>= 13:
            result = 'overflow'
            break
    print(f'#{tc} {result}')
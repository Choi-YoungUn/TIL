"""
binary_print: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('binary_print_input.txt')


T = int(input().strip())
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    binary = bin(M)[2:]
    result = 'ON'
    check = binary[len(binary)-N:]
    if N <= len(binary):
        for x in check:
            if x == '0':
                result = 'OFF'
                break
    else:
        result = 'OFF'
    print(f'#{tc} {result}')
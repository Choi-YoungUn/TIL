"""
binary: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('binary_input.txt')

T = int(input().strip())
for tc in range(1, T + 1):
    result = ''
    N, code = map(str, input().strip().split())
    for x in range(int(N)):
        t = format(int(code[x], 16), 'b')
        result += '0'*( 4 - len(t)) + t
    print(f'#{tc} {result}')
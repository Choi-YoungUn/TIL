"""
binary_three: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('binary_three_input.txt')

T = int(input().strip())
for tc in range(1, T + 1):
    N, K = map(int,input().split())
    maxx = 2 ** 50
    temp=[]
    for k in range(maxx):
        if k % 3 == 0:
            tmp_num = str(ord(k))
            
            temp.append(k)
    print(temp[:20])
"""
002_NtoMsum: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('002_NtoMsum_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    nm = list(map(int,input().split()))
    nums = list(map(int,input().split()))
    minn = 10000 * nm[0]
    maxx = nm[0]

    for x in range(nm[0] - nm[1] + 1):
        temp = 0
        for y in range(nm[1]):
            temp += nums[x + y]
        else:
            if temp <= minn:
                minn = temp
            if temp >= maxx:
                maxx = temp
            
    print("#%d %d" %(test_case, maxx - minn))
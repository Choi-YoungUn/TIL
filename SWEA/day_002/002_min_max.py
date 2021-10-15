"""
002_min_max: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('002_min_max_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    num = input()
    arr = list(map(int,input().split()))
    maxx = 1
    minn = 1000000

    for x in range(len(arr) ):
        if maxx < arr[x]:
            maxx = arr[x]
        if minn > arr[x]:
            minn = arr[x]

    
    result = maxx - minn

    print("#%d %d" %(test_case , result))
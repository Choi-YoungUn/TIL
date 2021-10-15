"""
003_lisum: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('003_lisum_input.txt')


T = 10
for test_case in range(1, T + 1):
    n = int(input())
    arr = list(map(int,input().split()))
    counts = 0
    for i in range(1 << n):
        temp = 0
        for j in range(n):
            if i & (1<< j):
                temp += arr[j]
        if temp == 0:
            counts += 1
    print("#%d %d" %(test_case , counts))
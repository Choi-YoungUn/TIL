"""
004_sum2: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('004_sum2_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    nk = list(map(int,input().split()))
    counts = 0
    k_list = list(range(1,13))
    for i in range(1 << 12):
        temp = []
        for j in range(len(k_list)):
            if i & (1<< j):
                temp.append(k_list[j])
        sum = 0
        if len(temp) == nk[0] :
            for x in range(len(temp)):
                sum += temp[x]
            if sum == nk[1]:
                counts += 1
        
                


        
    print("#%d %d" %(test_case , counts))
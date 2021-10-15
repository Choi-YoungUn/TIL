"""
004_binary_serch: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('004_binary_serch_input.txt')

def binary_serch(target, start, end):
    counts = 1
    while start < end:
        mid = (start + end ) // 2
        if mid == target:
            return counts
        elif mid > target:
            end = mid 
            counts += 1
        else:
            start = mid
            counts += 1
    else:
        return -1
    


T = int(input())
for test_case in range(1, T+1):
    total_a_b = list(map(int, input().split()))
    a = binary_serch(total_a_b[1], 1, total_a_b[0])
    b = binary_serch(total_a_b[2], 1, total_a_b[0])
    if a > b:
        result = 'B'
    elif a < b:
        result = 'A'
    else:
        result = '0'


    print("#{} {}".format(test_case, result))




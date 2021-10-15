"""
004_num_sort: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('004_num_sort_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    num = int(input())
    arr = list(map(int,input().split()))

    lists_len = len(arr)
    end = len(arr) - 1
    while end > 0:
        last_swap = 0
        for i in range(end):
            if arr[i] > arr[i + 1]:
                arr[i], arr[i + 1] = arr[i + 1], arr[i]
                last_swap = i
        end = last_swap
    temp =[]
    for x in range(len(arr)):
        temp.append(str(arr[x]))
    
    
    st = ' '.join(temp)
    print("#{} {}".format(test_case, st))
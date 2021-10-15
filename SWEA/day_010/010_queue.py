"""
010_queue: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('010_queue_input.txt')

for test_case in range(1, 11):
    tc = int(input())
    nums = list(map(int, input().split()))
    now = 0
    add = 1
    while nums[-1] > 0:
        temp = nums.pop(0) - add
        if temp < 0:
            temp = 0
        nums.append(temp)
        add += 1
        if add > 5:
            add = 1
    result = ' '.join(list(map(str, nums)))
    print("#{} {}".format(tc, result))

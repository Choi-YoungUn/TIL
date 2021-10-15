"""
project: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('project_input.txt')

def max_index(lists , start):
    temp = 0
    for x in range(start, len(lists)):
        if temp < lists[x]:
            temp = lists[x]
            result = x
    return result


T = int(input())
for test_case in range(1,T+1):
    day = int(input())
    cost = list(map(int,input().split()))
    money = 0
    max_in = 0
    x = 0
    while x < len(cost) -1:
        if x == max_in and x < len(cost) -1:
            max_in = max_index(cost, x + 1)
            if cost[x] > cost[max_in]:
                x += 1
        elif x < max_in:
            de = cost[max_in] - cost[x]
            money += cost[max_in] - cost[x]
            x += 1
        

    print("#{} {}".format(test_case , money))
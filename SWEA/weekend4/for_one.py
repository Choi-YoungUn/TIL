"""
for_one: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('for_one_input.txt')


def Find(num):
    if far[num] == num:
        return num
    px = Find(far[num])
    far[num] = px
    return px
 
def union(num1, num2):
    px = Find(num1)
    py = Find(num2)
    
    far[py] = px


import heapq
T = int(input())
for tc in range(1, T + 1):
    N = int(input())
    l_x = list(map(float, input().split()))
    l_y = list(map(float, input().split()))
    E = float(input())
    far = [num for num in range(N + 1)]
    result = 0
    hq = []
    for land in range(N-1):
        for next_land in range(land+1, N):
            cost = E * ((abs(l_x[land] - l_x[next_land]))**2 + (abs(l_y[land] - l_y[next_land]))**2)
            heapq.heappush( hq, (cost, land, next_land) )
    
    

    while hq:
        now = heapq.heappop(hq)
        now_cost = now[0]
        now_land = now[1]
        next_land = now[2]
        if Find(now_land) == Find(next_land):
            continue
        union(now_land, next_land)
        result += now_cost

    print(f'#{tc} {round(result)}')
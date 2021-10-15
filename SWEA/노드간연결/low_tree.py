"""
low_tree: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('low_tree_input.txt')


import heapq

T = int(input())
for tc in range(1, T + 1):
    V, E = map(int, input().split())
    Grape = [[] for _ in range(V + 1)]
    total_cost = 0
    for i in range(E):
        no1, no2, cost = map(int, input().split())
        Grape[no1].append( (cost, no2) )
        Grape[no2].append( (cost, no1) )

    hq = []
    visited = [False] * (V + 1)

    for cost, node in Grape[1]:
        heapq.heappush( hq, (cost, node) )
    visited[1] = True

    while hq:
        now = heapq.heappop(hq)
        now_cost = now[0]
        now_node = now[1]
        if visited[now_node]:
            continue

        total_cost += now_cost
        visited[now_node] = True
        for cost, node in Grape[now_node]:
            heapq.heappush( hq, (cost, node) )
    print(f'#{tc} {total_cost}')
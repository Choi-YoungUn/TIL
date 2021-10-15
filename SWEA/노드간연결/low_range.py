"""
low_range: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('low_range_input.txt')

import heapq
T = int(input())
for tc in range(1, T +1):
    N, E = map(int, input().split())
    tmp = [[]for _ in range(N+1)]
    load = [999999] * (N + 1)
    for _ in range(E):
        n1, n2, far = map(int, input().split())
        tmp[n1].append((far, n2))

    q = []
    heapq.heappush(q, (0, 0))
    load[0] = 0

    while q:
        now = heapq.heappop(q)
        now_far = now[0]
        now_node = now[1]

        for far, next in tmp[now_node]:
            if load[now_node] + far >= load[next]:
                continue
            load[next] = load[now_node] + far
            heapq.heappush(q, (load[next], next))

    print(f'#{tc} {load[N]}')
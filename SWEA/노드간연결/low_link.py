"""
low_link: 문제명을 입력해주세요 :)
"""

import sys, heapq
sys.stdin = open('low_link_input.txt')


T = int(input())
for tc in range(1, T +1):
    V, E = map(int, input().split())
    Graph = [[] for _ in range(V + 1)]
    using = [False] * (V+1)
    for _ in range(E):
        n1, n2, w = map(int, input().split())
        Graph[n1].append((w, n2))
        Graph[n2].append((w, n1))
    
    hq = []
    result = 0
    for line in Graph[0]:
        heapq.heappush( hq, line )
    
    using[0] = True

    while hq:
        now = heapq.heappop(hq)
        now_w = now[0]
        now_node = now[1]
        if using[now_node]:
            continue
        result += now_w
        using[now_node] = True
        for line in Graph[now_node]:
            heapq.heappush( hq, line )
    print(f'#{tc} {result}')
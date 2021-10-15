"""
insoo: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('insoo_input.txt')


def dijstra(start, end , node):
    global result
    dist = [999999999] * (N + 1)
    hq =[]
    heapq.heappush( hq, (0, start))
    dist[start] = 0
    while hq:
        now = heapq.heappop(hq)
        now_far = now[0]
        now_node = now[1]
        if now_node == end:
            result[start_node] += now_far
            break
            
        for far, node in Graph[now_node]:
            if dist[now_node] + far >= dist[node]:
                continue
            dist[node] = dist[now_node] + far
            heapq.heappush(hq, (dist[node], node))



import heapq
T = int(input())
for tc in range(1, T + 1):
    N, M ,X = map(int, input().split())

    Graph = [ [] for _ in range(N + 1) ]
    visited = [False] * (N + 1)
    
    result = [0]  * (N + 1)
    for a in range(M):
        N1, N2 , Far = map(int, input().split())
        Graph[N1].append((Far, N2))
        
    
    for start_node in range(1,N+1):
        dijstra(start_node, X ,start_node)
        dijstra(X, start_node, start_node)
        # dist = [999999999] * (N + 1)
        # hq =[]
        # heapq.heappush( hq, (0, start_node))
        # dist[start_node] = 0
        # while hq:
        #     now = heapq.heappop(hq)
        #     now_far = now[0]
        #     now_node = now[1]
        #     if now_node == X:
        #         result[start_node] = now_far
        #         break
                

        #     for far, node in Graph[now_node]:
        #         if dist[now_node] + far >= dist[node]:
        #             continue
        #         dist[node] = dist[now_node] + far
        #         heapq.heappush(hq, (dist[node], node))
        # dist = [999999999] * (N + 1)
        # hq =[]
        # heapq.heappush( hq, (0, X))
        # dist[X] = 0
        # while hq:
        #     now = heapq.heappop(hq)
        #     now_far = now[0]
        #     now_node = now[1]
        #     if now_node == start_node:
        #         result[start_node] += now_far
        #         break
                

        #     for far, node in Graph[now_node]:
        #         if dist[now_node] + far >= dist[node]:
        #             continue
        #         dist[node] = dist[now_node] + far
        #         heapq.heappush(hq, (dist[node], node))
    print(f'#{tc} {max(result)}')

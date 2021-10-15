# prim
"""
6 11
0 1 32
0 2 31
0 5 60
0 6 51
1 2 21
2 4 46
2 6 25
3 4 34
3 5 18
4 5 40
4 6 51
"""

import heapq

n, m = map(int, input().split())
Graph = [[] for _ in range(n + 1)]
total_cost = 0
#인접리스트
for i in range(m):
    f, t, cost = map(int, input().split())
    Graph[f].append( (cost, t) )
    Graph[t].append( (cost, f) )
# 1. 그래프 구성

hq = []
visited = [False] * (n + 1) # 같은 그룹에 포함시켰는가?
# 2. 큐 선언 -> heap선언


# 3. 시작점(0번 점) 세팅 -> 시작점에 연결된 선 모두 heap에 추가
for cost, t in Graph[0]:
    heapq.heappush( hq, (cost, t) )
visited[0] = True

while hq:
    # 4. now점 꺼내기 -> now 선 (가장 짧은 선)
    now = heapq.heappop(hq)
    now_cost = now[0]
    now_t = now[1]
    # 5. 이 선이 새로운 점을 연결하는 선인가? <- next찾기(판별)
    if visited[now_t]:
        continue
    total_cost += now_cost
    # 6. 새로운점 연결 <- next를 큐에 추가
    visited[now_t] = True
    for cost, t in Graph[now_t]:
        heapq.heappush( hq, (cost, t) )
print(total_cost)
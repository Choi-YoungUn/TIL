# dijkstra smaple code
"""
1 2 4
1 3 11
1 4 7
2 5 25
3 7 46
4 5 18
4 6 1
5 8 13
6 7 50
6 8 4
7 9 1000
8 9 77
"""
# 최소 신장 트리
import heapq

V, E = 9, 12
Graph = [ [] for _ in range(V + 1) ]
visited = [False] * (V + 1)
dist = [2134567890] * (V + 1) # 시작점부터의 거리
for _ in range(E):
    f, t, cost = map(int, input().split())
    Graph[f].append( (cost, t) )
    Graph[t].append( (cost, f) )
# 1. 그래프 구성

q = []
# 2. 힙 생성

heapq.heappush(q, (0, 1))
dist[1] = 0
# 3. 시작점 세팅
while q:
    now = heapq.heappop(q)
    now_cost = now[0]
    now_num = now[1]
    # 4. now를 꺼냄 (now : 지금 확정할 수 있는 점)

    # 5. next 찾기
    for cost, to in Graph[now_num]:
        if dist[now_num] + cost >= dist[to]:
            continue # now를 거쳐 가는 방법이 전에 찾아놨던 방법보다 멀다.
        dist[to] = dist[now_num] + cost # now를 거쳐가는 방법이 더 이득이면 갱신
        heapq.heappush(q, (dist[to], to) )
de = 1
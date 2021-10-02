import sys
from collections import deque


def dfs(now):
    visited_dfs[now] = 1
    print(now, end= ' ')
    for x in range(1, N+1):
        if lists[now][x] == 1 and visited_dfs[x] == 0:
            visited_dfs[x] = 1
            dfs(x)


def bfs():
    while bfs_que:
        now_num = bfs_que[0]
        print(now_num, end=' ')
        bfs_que.popleft()
        for next in range(1, N+1):
            if visited_bfs[next] == 0 and lists[now_num][next] == 1:
                bfs_que.append(next)
                visited_bfs[next] = 1
        

N, M, V = map(int, sys.stdin.readline().split())

temp =[list(map(int, sys.stdin.readline().split()))for _ in range(M)]
visited_dfs = [0] * (N+1)
visited_bfs = [0] * (N+1)
lists = [[0] * (N+ 1) for _ in range(N+ 1)]
bfs_que = deque()
for now, next in temp:
    lists[now][next] = 1
    lists[next][now] = 1
dfs(V)
bfs_que.append(V)
visited_bfs[V] = 1
print()
bfs()
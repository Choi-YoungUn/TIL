# 문명
import sys
from collections import deque

def Find(a):
    if a == parents[a]:
        return a
    pa = Find(parents[a])
    parents[a] = pa
    return pa

def Union(a, b):
    pa = Find(a)
    pb = Find(b)
    parents[pb] = pa

def grouping(x, y, cnt):
    # 해당 좌표의 주변을 확인하여 문명이 있으면 해당 좌표의 문명과 병합
    dx = [-1,1,0,0]
    dy = [0,0,-1,1]
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        if not( 0< nx <= n and 0 < ny <= n):
            continue # 맵을 벗어난 상황
        if MAP[nx][ny] == 0:
            continue # 인접한곳에 문명이 X
        if Find(MAP[nx][ny]) == Find(MAP[x][y]):
            continue # 인접한곳에 이미 병합된 문명
        Union(MAP[nx][ny], MAP[x][y])
        global ans
        ans = cnt

def bfs():
    while q:
        now = q.popleft()
        x = now[0]
        y = now[1]
        cnt = now[2]
        dx = [-1,1,0,0]
        dy = [0,0,-1,1]
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if not (0 < nx <= n and 0 < ny <= n):
                continue  # 맵을 벗어난 상황
            if MAP[nx][ny] != 0:
                continue # 이미 문명이 존재하면 무시
            MAP[nx][ny] = MAP[x][y]
            grouping(nx, ny, cnt)
            q.append( (nx, ny, cnt + 1) )


n, k = map(int, sys.stdin.readline().split())
MAP = [ [0] * (n + 2) for _ in range(n + 2) ]
    # 1. 그래프 구성 <- MAP
parents = [i for i in range(k + 1)]
# 문명이 있으면 해당 문명의 번호
q = deque()
    # 2. 큐 생성
for i in range(1, k + 1):
    x, y = map(int, sys.stdin.readline().split())
    MAP[x][y] = i
    grouping(x, y, 0)
    q.append( [x, y, 1] )
    # 3. 시작점 세팅
# 입력받은 x, y들이 인접한 경우
ans = 0
bfs()
print(ans)
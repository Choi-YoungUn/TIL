from collections import deque
import sys


N, M, T = map(int, sys.stdin.readline().split())
MAP = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]
visited = [[0] * M for _ in range(N)]
# 1. 그래프 구조

# 2. queue생성
q = deque()

# 3. 시작점 세팅
visited[0][0] = 1
q.append([0,0])
#7. 4~6 단계 반복
while q:
    # 4. now 꺼내기
    now = q.popleft()
    now_row = now[0]
    now_col = now[1]

    # 5. next찾기
    dr = [-1,1,0,0]
    dc = [0,0,-1,1]
    for i in range(4):
        next_row = now_row + dr[i]
        next_col = now_col + dc[i]
        if next_row < 0 or next_col < 0 or next_col >= M or next_row >= N:
            continue # 맵을 벗어가는가
        if MAP[next_row][next_col] == 1:
            continue # 벽이 있는가?
        if visited[next_row][next_col] != 0:
            continue #전에 찾은 적 있는 좌표면 무시

        # 6. next를 queue에 추가
        visited[next_row][next_col] = visited[now_row][now_col] + 1
        q.append([next_row, next_col])


# 1. 검을 획득하지 않고 바로 가는 방법
ans1 = visited[N-1][M-1] - 1
# 2. 검을 획득하고 가는 방법
ans2 = -1
s_row = -1
s_col = -1
for row in range(N):
    for col in range(M):
        if MAP[row][col] == 2:
            ans2 = visited[row][col] - 1
            s_row = row
            s_col = col
# 검까지의 거리
# 검 -> 도착지
if ans2 != -1:#검을 획득하지 못하는 경우 필터링
    ans2 += (N - s_row - 1) + (M - s_col - 1)
ans = 0
if ans1 == -1: # 검을 획득하지 않고 갈 수 없다.
    ans = ans2
elif ans2 == -1:
    ans = ans1
else :
    ans = min(ans1, ans2)
# 바로 가지도 못하고 검을 획득하지도 못하는 경우
if ans <= T and ans != -1:
    print(ans)
else :
    print("Fail")
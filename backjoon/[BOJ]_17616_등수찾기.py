from collections import deque
import sys

N, M, X = map(int, sys.stdin.readline().split())
data_up = [[] for _ in range(N + 1)] # 더 잘본 얘들
data_down = [[] for _ in range(N + 1)] # 더 못본 얘들

for _ in range(M):
    A, B = map(int, sys.stdin.readline().split())
    data_down[A].append(B)
    data_up[B].append(A)
# 그래프 구성

# 1) 더 못본얘들 위주
# 2. queue생성
q = deque()
visited = [0] * (N + 1)
# 3. 시작점 세팅
visited[X] = 1
q.append(X)
# 7. 4~6단계 반복
cnt = 0# 나보다 몇 명이 못봤는지
while q:
    # 4. now꺼내기
    now = q.popleft()
    cnt += 1
    # 5. now에서 갈 수 있는 next
    for next in data_down[now]:
        if visited[next] != 0:
            continue
        #6. next를 queue에 추가
        visited[next] = 1
        q.append(next)
ans1 = N - cnt + 1 # 최소 등수

# 1) 더 못본얘들 위주
# 2. queue생성
q = deque()
visited = [0] * (N + 1)
# 3. 시작점 세팅
visited[X] = 1
q.append(X)
# 7. 4~6단계 반복
cnt = 0# 나보다 몇 명이 못봤는지
while q:
    # 4. now꺼내기
    now = q.popleft()
    cnt += 1
    # 5. now에서 갈 수 있는 next
    for next in data_up[now]:
        if visited[next] != 0:
            continue
        #6. next를 queue에 추가
        visited[next] = 1
        q.append(next)
ans2 = cnt
print(ans2, ans1)
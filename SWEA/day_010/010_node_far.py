"""
010_node_far: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('010_node_far_input.txt')

from collections import deque

def go_node(now_node):
    for x in range(V + 1):
        if node_line[now_node][x] == 1 and visited[x] == -1:
            Q.append(x)
            visited[x] = visited[now_node] + 1
    Q.popleft()
    if len(Q) > 0:
        go_node(Q[0])
    
T = int(input())
for tc in range(1, T + 1):
    V, E = map(int,input().split())
    node_line_in = [list(map(int, input().split())) for _ in range(E)]
    S, G = map(int,input().split())
    node_line = [[0] * (V + 1) for _ in range(V + 1)]
    Q = deque()
    Q.append(S)
    visited = [-1] * (V + 1)
    visited[S] = 0
    for x in range(E):
        node_line[node_line_in[x][0]][node_line_in[x][1]] = 1
        node_line[node_line_in[x][1]][node_line_in[x][0]] = 1

    go_node(Q[0])
    if visited[G] == -1:
        print("#{} {}".format(tc, visited[G] + 1))
    else:
        print("#{} {}".format(tc, visited[G]))


"""
# BFS

T = int(input())
for tc in range(T):
    N = int(input())
    G = [ [] for in range(N) ]
    # 1. 연결 구조를 구성
    입력
    a b
    G[a].append(b)

    # 2. queue 생성(append, pop활용 version)
    q = []

    # 3. 시작점 세팅(시작점을 queue에 추가)
    q.append(시작점 번호)
    
    while len(q) != 0:
        # 4. queue에서 맨 앞 점를 꺼냄(now)
        # ---- 추가적인 계산이 필요한 경우 여기서
        now = q.pop(0)

        # 5. now에서 갈 수 있는 모든 점을 찾기(next)
        for next in G[now]:
            
            #6. next를 queue에 추가
            q.append(next)
            

    
1. 연결 구조를 구성
2. queue 생성
3. 시작점 세팅
----준비---
4. queue에서 맨 앞 점를 꺼냄(now)
5. now에서 갈 수 있는 모든 점을 찾기(next)
6. next를 queue에 넣기
7. 4~6번 단계를 queue가 비워질 때까지

--- 기본 구성 완료 ----
옵션 : 
1. 맵을 벗어나는가? : 2차원맵 한정
2. 갈 수 없는 점 확인
3. 갔던 점을 다시 돌아갈 수 있는가? <- visited배열 활용
   visited : 내가 찾은 점인가?

---- 살짝 응용 ----
1. 몇 번 만에 갈 수 있는가?
   visited : 내가 몇 번만에 찾은 점인가?

실제 BFS가 어디서 활용되느냐!!!!!!!!
1. 제일 적게 다른 점을 들려서 가는 방법
    -BFS에서 어떤 점을 발견하면 그 점이 가장 빠른 타이밍에 발견 된 것이다.

    """

# from collections import deque

# T = int(input())
# for tc in range(T):
#     V, E = map(int, input().split())
#     """ # 인접 행렬
#     G = [ [0] * (V+1) for _ in range(V + 1) ] 
#     for _ in range(E):
#         FROM, TO = map(int, input().split())
#         G[FROM][TO] = 1
#         G[TO][FROM] = 1
#     """

#     """
#     # 인접 리스트
#     G = [ [] for _ in range(V + 1) ]
    
#     for _ in range(E):
#         FROM, TO = map(int, input().split())
#         G[FROM].append(TO)
#         G[TO].append(FROM)
#     """


#     G1 = [ [0] * (V+1) for _ in range(V + 1) ]
#     G2 = [ [] for _ in range(V + 1) ]
#     for _ in range(E):
#         FROM, TO = map(int, input().split())
#         G1[FROM][TO] = 1
#         G1[TO][FROM] = 1
#         G2[FROM].append(TO)
#         G2[TO].append(FROM)
#     # 1. 연결 구조를 구성

#     # 2. queue 생성
#     q = [] # pop, append
#     q = deque() # deque방식
#     q = [0] * (V+1) # front, rear
#     visited = [0] * (V + 1)

#     front = 0
#     rear = 0

#     # 3. 시작점 세팅
#     s, g = map(int, input().split())
#     visited[s] = 1 # <- 조심 0의 의미가 이미 있어요(내가 아직 찾지 못한 점이다.)

#     q[rear] = s
#     rear = (rear + 1) % len(q)

#     # 7. 4~6단계를 반복
#     while front != rear:
#         # 4.queue에서 맨 앞 점를 꺼냄(now)
#         now = q[front]
#         front = (front + 1) % len(q)
#         # 5. now에서 갈 수 있는 모든 점을 찾기(next)
#         for next in G2[now]:
#             if visited[next] != 0:
#                 continue
#             # 6. next를 queue에 넣기
#             visited[next] = visited[now] + 1
#             q[rear] = next
#             rear = (rear + 1) % len(q)

#         """
#         # 5. now에서 갈 수 있는 모든 점을 찾기(next)
#         for next in range(1, V+1):
#             if G1[now][next] == 1:
#                 # now -> next로 가는 선이 있다!

#                 #6. next를 queue에 넣기
#                 q[rear] = next
#                 rear = (rear + 1) % len(q)
#         """
#     if visited[g] == 0:
#         print("#{} {}".format(tc + 1, 0))
#     else :
#         print("#{} {}".format(tc + 1, visited[g] - 1))
# """
# 옵션 : 
# 1. 맵을 벗어나는가? : 2차원맵 한정
# 2. 갈 수 없는 점 확인
# 3. 갔던 점을 다시 돌아갈 수 있는가? <- visited배열 활용
#    visited : 내가 찾은 점인가?
#    ---- 살짝 응용 ----
# 1. 몇 번 만에 갈 수 있는가?
#    visited : 내가 몇 번만에 찾은 점인가?
# """
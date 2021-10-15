"""
007_node_line: 문제명을 입력해주세요 :)
"""
import sys
sys.stdin = open('007_node_line_input.txt')

# fin_nodes = []

# def dfs(start ,end, to_nodes):
#     visit = [0] * (to_nodes + 1)
#     stack = []
#     now = start
#     visit[now] = 1
#     while now != 0:
#         for x in range(1, to_nodes + 1):
#             if fin_nodes[now][x] == 1 and visit[x] == 0:
#                 stack.append(now)
#                 now = x
#                 if x == end:
#                     return 1
#                 visit[now] = 1
#                 break
#         else:
#             if stack:
#                 now = stack.pop()
#             else:
#                 now = 0
#                 break
#     return 0

# T = int(input())
# for test_case in range(1, T + 1):
#     ve = list(map(int, input().split()))
#     nodes = []
#     fin_nodes.clear()
    
#     for x in range(ve[0] + 1):
#         fin_nodes.append([0] * (ve[0]+1))
    
#     for x in range(ve[1]):
#         nodes.append(list(map(int, input().split())))
#         fin_nodes[nodes[x][0]][nodes[x][1]] = 1

#     st_end = list(map(int, input().split()))
    
#     print("#{} {}".format(test_case, dfs(st_end[0], st_end[1], ve[0])))


def dfs(now): # now : 나의 현재 위치
    # 2. 기저조건(옵션)
    # 1. now에서 갈 수 있는 next찾기
    for to in range(V + 1):
        if adj[now][to] == 1 and visited[to] == 0:
            # adj[now][to] == 1 : now에서 to로 갈 수 있는 길이 있는가?
            visited[to] = 1 # to에 간다!라고 기록
            dfs(to) # 길이 있으면 가라!

    # 3. 문제가 생길 수 있는 경우

T = int(input())
for tc in range(T):
    V, E = map(int, input().split())
    adj = [[0] * (V + 1) for _ in range(V + 1)]
    visited = [0] * (V + 1) # 들렸던 점인가?
    # adj[from][to]
    for i in range(E):
        f, t = map(int, input().split())
        # f : 어디에서
        # t : 어디로
        adj[f][t] = 1
    start, end = map(int, input().split())
    visited[start] = 1
    dfs(start) # start에서부터 갈 수 있는 모든 곳으로 전부 가보게 된다.
    print("#{} {}".format(tc + 1, visited[end])) # <- 갔던 점인가?
# import sys
# from collections import deque


# N, R, Q = map(int, sys.stdin.readline().split())
# Node_1 = [[0] * (N+1) for _ in range(N+1)]
# Node_2 = [[0] * (N+1) for _ in range(N+1)]

# queus = deque()

# for _ in range(N-1):
#     U, V = map(int, sys.stdin.readline().split())
#     Node_1[U][V] = 1
#     Node_1[V][U] = 1
#     Node_2[U][V] = 1

# spot = [int(sys.stdin.readline().strip())for _ in range(Q)]

# for start in spot:
#     li = [start]
#     vistied = [0] * (N+1)
    
#     queus.append(start)
#     now = queus.popleft()
#     vistied[now] = 1
    
#     for next in range(1, N+1):
#         if Node_2[now][next] == 1 and vistied[next] == 0:
#             vistied[next] = 1
#             queus.append(next)
#             li.append(next)
#     while queus:
#         now = queus.popleft()
#         vistied[now] = 1
#         for next in range(1, N+1):
#             if Node_1[now][next] == 1 and vistied[next] == 0:
#                 queus.append(next)
#                 li.append(next)
#     print(len(li))


# import sys
# from collections import deque

# N, R, Q = map(int, sys.stdin.readline().split())
# Node_equl = [[x] for x in range(0, N+1)]
# Node_non_equl = [[x] for x in range(0, N+1)]
# queus = deque()
# for _ in range(N-1):
#     U, V = map(int, sys.stdin.readline().split())
#     Node_equl[U].append(V)
#     Node_equl[V].append(U)
#     Node_non_equl[U].append(V)

# spot = [int(sys.stdin.readline().strip())for _ in range(Q)]

# for start in spot:
#     li = [start]
#     vistied = [0] * (N+1)
#     cnt = 1
#     vistied[start] = 1
#     for next in range(1, len(Node_non_equl[start])):
#         tmp = Node_non_equl[start][next]
#         vistied[tmp] = 1
#         queus.append(tmp)
#         cnt += 1
#     while queus:
#         now = queus.popleft()
#         for next in range(1, len(Node_equl[now])):
#             tmp = Node_equl[now][next]
#             if vistied[tmp] == 0:
#                 vistied[tmp] = 1
#                 queus.append(tmp)
#                 cnt += 1
#     print(cnt)


import sys
sys.setrecursionlimit(1000000)

def dfs(now):
    vistied[now] = 1
    for x in Node[now]:
        if vistied[x] == 0 :
            dfs(x)
            vistied[now] += vistied[x]

N, R, Q = map(int, sys.stdin.readline().split())
Node = [[] for _ in range(N+1)]
vistied = [0] * (N+1)

for _ in range(N-1):
    U, V = map(int, sys.stdin.readline().split())
    Node[U].append(V)
    Node[V].append(U)

dfs(R)
spot = [int(sys.stdin.readline().strip())for _ in range(Q)]
for x in spot:
    print(vistied[x])
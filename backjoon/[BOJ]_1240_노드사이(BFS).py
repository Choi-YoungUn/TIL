import sys
from collections import deque


NM = list(map(int, sys.stdin.readline().split()))
tree = [[ ] for _ in range(NM[0])]

for _ in range(NM[0] -1):
    node = list(map(int, sys.stdin.readline().split()))
    tree[node[0]-1].append([node[1]-1, node[2]])
    tree[node[1]-1].append([node[0]-1, node[2]])


for _ in range(NM[1]):
    q = deque()
    visied = [0] * NM[0]
    goto = list(map(int, sys.stdin.readline().split()))
    q.append([goto[0] - 1, 0])
    visied[goto[0] - 1] = 1
    while q:
        now = q.popleft()
        now_node = now[0]
        if now_node == goto[1] - 1 :
            print(now[1])
            break

        for next in tree[now_node]:
            if visied[next[0]] == 0:
                visied[next[0]] = 1
                q.append([next[0], now[1] + next[1]])
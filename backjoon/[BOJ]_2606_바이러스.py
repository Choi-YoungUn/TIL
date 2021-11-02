import sys
from collections import deque

N = int(sys.stdin.readline())
com_line = [[] for _ in range(N + 1)]
for _ in range(int(sys.stdin.readline())):
    node1, node2 = map(int, sys.stdin.readline().split())
    com_line[node1].append(node2)
    com_line[node2].append(node1)
hacked = [0] * (N + 1)
q = deque()
q.append(1)
while q:
    now_node = q.popleft()
    hacked[now_node] = 1
    
    for x in com_line[now_node]:
        if hacked[x] == 0:
            q.append(x)
result = sum(hacked)

print(result -1)
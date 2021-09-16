#  토마토 3D

import sys
from collections import deque

def check():
    global result 
    for k in range(H):
        for i in range(N):
            if 0 in BOX[k][i]:
                result = -1
            

M, N, H = map(int, sys.stdin.readline().split())
BOX =  [[]] 
for z in range(H):
    for y in range(N):
        BOX[z].append(list(map(int, sys.stdin.readline().split())))
    BOX.append([])
BOX.pop()
Q = deque()
for k in range(H):
    for i in range(N):
        for j in range(M):
            if BOX[k][i][j] == 1:
                Q.append([k,i,j])

result = 0
while Q:
    now_k = Q[0][0]
    now_i = Q[0][1]
    now_j = Q[0][2]
    for move in range(6):
        dk = [-1, 1, 0, 0, 0, 0]
        di = [0, 0, -1, 1, 0, 0]
        dj = [0, 0, 0, 0, -1, 1]
        next_k = now_k + dk[move]
        next_i = now_i + di[move]
        next_j = now_j + dj[move]
        if 0 <= next_k < H and 0 <= next_i < N and 0 <= next_j < M:
            if BOX[next_k][next_i][next_j] == 0:
                Q.append([next_k, next_i, next_j])
                BOX[next_k][next_i][next_j] = BOX[now_k][now_i][now_j] + 1
                result = max(result, BOX[now_k][now_i][now_j])
    Q.popleft()

check()
print(result)
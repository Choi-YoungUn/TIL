import sys
from collections import deque
T = int(sys.stdin.readline().strip())
for tc in range(1, T + 1):
    maps_size = int(sys.stdin.readline().strip())
    now_x, now_y = map(int, sys.stdin.readline().split())
    go_x, go_y = map(int, sys.stdin.readline().split())
    maps = [[0] * maps_size for _ in range(maps_size)]
    maps[go_x][go_y] = -1
    maps[now_x][now_y] = 1
    stack = deque()
    stack.append([now_x, now_y])
    if now_x == go_x and now_y == go_y:
        stack = []
    while stack:
        now_x, now_y = stack.popleft()
        di = [-1, -2, -2, -1, 1, 2, 2, 1]
        dj = [-2, -1, 1, 2, 2, 1, -1, -2]
        for move in range(8):
            next_x = now_x + di[move]
            next_y = now_y + dj[move]
            if 0 <= next_x < maps_size and 0 <= next_y < maps_size:
                if maps[next_x][next_y] == 0:
                    stack.append([next_x, next_y])
                    maps[next_x][next_y] = maps[now_x][now_y] + 1
                elif maps[next_x][next_y] == -1:
                    maps[next_x][next_y] = maps[now_x][now_y] + 1
                    stack = []
                    break
                

    print(maps[go_x][go_y] - 1)

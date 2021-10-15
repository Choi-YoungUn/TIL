"""
squl_room: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('squl_room_input.txt')
sys.setrecursionlimit(10000)


def dfs(nowx, nowy, cnt, startx , starty):
    global result, start_pox, start_poy
    move = False
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]
    for add in range(4):
        next_x = nowx + dx[add]
        next_y = nowy + dy[add]
        if 0 <= next_x < N and 0 <= next_y < N:
            if MAP[nowx][nowy] == MAP[next_x][next_y] - 1:
                move = True
                dfs(next_x, next_y, cnt+1, startx , starty)
    if move == False:
        if result < cnt:
            result = cnt
            start_pox = startx
            start_poy = starty
        elif result == cnt:
            if MAP[start_pox][start_poy] > MAP[startx][starty]:
                start_pox = startx
                start_poy = starty
        return
        

T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input())
    MAP = [list(map(int, input().split()))for _ in range(N)]
    result = 0
    start_pox = 0
    start_poy = 0
    
    for x in range(N):
        for y in range(N):
            dfs(x, y, 0, x, y)
    
    print(f'#{tc} {MAP[start_pox][start_poy]} {result+1}')
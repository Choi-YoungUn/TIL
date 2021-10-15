"""
num_add: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('num_add_input.txt')

def dfs(nowx, nowy, string):
    
    if len(string) >= 7 :
        box.add(string)
        return
    dx = [-1, 1, 0, 0]
    dy = [0, 0, -1, 1]
    for add in range(4):
        next_x = nowx + dx[add]
        next_y = nowy + dy[add]
        if 0 <= next_x < 4 and 0 <= next_y < 4:
            
            dfs(next_x, next_y, string +  MAP[next_x][next_y])


T = int(input().strip())
for tc in range(1, T + 1):
    MAP = [list(input().split())for _ in range(4)]
    box = set()
    result = ''
    for x in range(4):
        for y in range(4):
            dfs(x,y, MAP[x][y])

    print(f'#{tc} {len(box)}')
    
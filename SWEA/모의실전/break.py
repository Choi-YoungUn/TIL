"""
break: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('break_input.txt')

import copy
from collections import deque

# def break_MAP(br_y):
#     global  MAP_copy, cnt
#     vistied = [[0]* W for _ in range(H)]
#     dx = [-1, 1, 0, 0]
#     dy = [0, 0, -1, 1]
#     #제일 윗부분 찾기
#     br_x = 0
#     for x in range(H):
#         if MAP_copy[x][br_y] != 0:
#             br_x = x
#             break

#     # 깎으면서 건든 곳 저장해서 깎기
#     both_break = deque()
#     both_break.append([br_x, br_y])
#     while both_break:
#         break_x = both_break[0][0]
#         break_y = both_break[0][1]
#         break_step = MAP_copy[break_x][break_y]
#         if MAP_copy[break_x][break_y] > 0:
#             MAP_copy[break_x][break_y] = 0

#         both_break.popleft()
#         for add in range(4):
#             #4방향 나가깎기
#             for step in range(1, break_step):

#                 del_x = break_x + dx[add] * step
#                 del_y = break_y + dy[add] * step
#                 # 4방향 깎기
#                 if 0 <= del_x < H and 0 <= del_y < W:
#                     if MAP_copy[del_x][del_y] > 1:
#                         both_break.append([del_x, del_y])
#                     elif MAP_copy[del_x][del_y] == 1:
#                         MAP_copy[del_x][del_y] = 0

#     for y in range(W):
#         ch_zero = -1
#         ch_num = -1

#         for x in range(H-1, -1, -1):
#             #0을 찾음
#             if MAP_copy[x][y] == 0 and ch_zero == -1:
#                 ch_zero = x
#             if MAP_copy[x][y] != 0:
#                 ch_num = x
#             if ch_zero != -1 and ch_num != -1 and (ch_zero > ch_num):
#                 MAP_copy[ch_zero][y],  MAP_copy[ch_num][y] = MAP_copy[ch_num][y] , MAP_copy[ch_zero][y] 
#                 ch_zero -= 1
#                 ch_num = -1
    
    
    
# def dfs(now, path):
#     if now >= N:
#         moves.add(path)
#         return
#     for i in range(W):
#         dfs(now+1, path+str(i))
    


# T = int(input())
# for tc in range(1, T + 1):
#     N, W, H = map(int, input().rstrip().split())
#     MAP = [list(map(int, input().rstrip().split())) for _ in range(H)]

#     moves = set()
    
#     dfs(0, '')
#     result = W * H +1
#     for go in moves:
#         cnt = 0
#         MAP_copy = copy.deepcopy(MAP)
#         for num in range(N):
#             break_MAP(int(go[num]))
        
#         for x in range(H):
#             for y in range(W):
#                 if MAP_copy[x][y] != 0:
#                     cnt += 1
        
#         if cnt < result:
#             result = cnt
#     if result == W * H +1:
#         result == 0
#     print(f'#{tc} {result}')

# 벽돌 깨기
import copy
from collections import deque

def make_path(now = 0, path = []):
    if now == N:
        path_set.add(tuple(path))
        path_list.append(path)
        return
    for i in range(W):
        # 구슬을 떨어뜨릴 위치 0 ~ w - 1
        make_path(now + 1, path + [i])

def copy_map():
    temp_MAP = [[0]*W for _ in range(W)]
    for row in range(H):
        for col in range(W):
            temp_MAP[row][col] = MAP[row][col]
    return temp_MAP

def break_block(temp_map, col):
    # 이번에 터질 부분 터트리기
    # temp_map의 col번째 열을 터트린다.
    # bfs

    # 1. 그래프 구성 <- temp_map

    # 2. queue생성 [0] : row, [1] : col, [2] : size
    q = deque()

    # 3. 시작점 세팅
    for row in range(H):
        if temp_map[row][col] != 0:
            q.append( (row, col, temp_map[row][col]) )
            temp_map[row][col] = 0 # 이 블록은 터졌다.
            break
    while q:
        #4. now꺼내기
        now = q.popleft()
        now_row = now[0]
        now_col = now[1]
        now_size = now[2]

        dr = [-1,1,0,0]
        dc = [0,0,-1,1]
        # 5. next찾기 : now로 인해 터질 벽돌 찾기
        for i in range(4):
            for size in range(now_size):
                next_row = now_row + dr[i] * size # ------
                next_col = now_col + dc[i] * size # ------

                if not( 0 <= next_row < H and 0<= next_col < W):
                    continue
                if temp_map[next_row][next_col] == 0:
                    continue

        # 6. 찾은 next를 추가하기
                q.append((next_row, next_col, temp_map[next_row][next_col]))
                temp_map[next_row][next_col] = 0 # 터트리기

def drop_block(temp_map):
    # temp_map을 확인하면서 벽돌 떨어트리기
    for col in range(W):
        cnt = 0
        for row in range(H-1, -1, -1):
            if temp_map[row][col] == 0:
                cnt += 1
            else :
                temp_map[row + cnt][col] = temp_map[row][col]
            # 아래서 위 방향으로 확인함
            # 빈 공간의 개수 counting
            # 빈 공간이 아니면 빈 공간의 개수만큼 아래로 떨어트림
        for row in range(cnt):
            temp_map[row][col] = 0
            # 빈칸 세팅

def count_block(temp_map): # 맵의 벽돌 개수 counting
    cnt = 0
    for rowMAP in temp_map:
        for block in rowMAP:
            if block != 0:
                cnt += 1
    return cnt

def pro():
    ans = count_block(MAP)
    # 순서대로 처리
    make_path() # 구슬을 떨어뜨릴 순열 만들기
    #temp_map = copy_map()
    for path in path_set:
        temp_map = copy.deepcopy(MAP)
        for now in path:
            break_block(temp_map, now) # 터트리기만 함
            # 터트려서 빈 공간이 생기면 빈 공간만큼 벽돌들이 떨어져야함
            if path == (2, 2, 6):
                de = 1
            drop_block(temp_map)
        ans = min(ans, count_block(temp_map))
    return ans


t = int(input())
for tc in range(t):
    N, W, H = map(int, input().split())
    MAP = [list(map(int, input().split())) for _ in range(H)]
    path_set = set()
    path_list = []
    print(f"#{tc + 1} {pro()}")
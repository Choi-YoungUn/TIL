import sys
def go(now_i, now_j, cnt):
    global max_cnt
    di = [-1, 1, 0, 0]
    dj = [0, 0, -1, 1]
    max_cnt = max(max_cnt, cnt)
    for x in range(4):
        next_i = now_i + di[x]
        next_j = now_j + dj[x]
        if 0 <= next_i <= R - 1 and 0 <= next_j <= C - 1:
            if chack[ord(maps[next_i][next_j])] == 0:
               chack[ord(maps[next_i][next_j])] = 1
               go(next_i, next_j, cnt + 1)
               
               chack[ord(maps[next_i][next_j])] = 0



R, C = map(int, sys.stdin.readline().split())

maps = [sys.stdin.readline().strip() for _ in range(R)]
stack = []
stack.append(maps[0][0])

max_cnt = 0
chack = [0] * 256
chack[ord(maps[0][0])] = 1
go(0,0, 1)
print(max_cnt)
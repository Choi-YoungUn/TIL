import sys

N = int(sys.stdin.readline().rstrip())
MAP = [[0]* 100 for _ in range(100)]
for _ in range(N):
    y, x = map(int, sys.stdin.readline().rstrip().split())
    for ch_x in range(x, x+10):
        for ch_y in range(y, y+10):
            if MAP[ch_x][ch_y] == 0:
                MAP[ch_x][ch_y] = 1
                DE = 1
    cnt = 0
    for cx in range(100):
        for cy in range(100):
            if MAP[cx][cy] == 1:
                cnt +=1
print(cnt)

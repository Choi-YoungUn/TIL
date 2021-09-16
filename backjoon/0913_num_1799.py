import sys

num = int(sys.stdin.readline())

box = [list(map(int,sys.stdin.readline().split())) for _ in range(num)]
visited = [[0]*num for _ in range(num)]

temp = []
count = 0
di = [-1, 1, 1, -1]
dj = [1, 1, -1, -1]
for y in range(num):
    for x in range(num):
        if box[y][x] == 1 and visited[y][x] == 0:
            count += 1
            visited[y][x] = 1
            temp.append([x, y])
            for check in range(4):
                gox = x + di[check]
                goy = y + dj[check]

                go = 1
                while 0 <= gox < num and 0<= goy < num :
                    visited[goy][gox] = 1
                    gox +=  + di[check]
                    goy +=  + dj[check]
print(count)
import sys

peo = int(sys.stdin.readline())
box = [list(map(int,sys.stdin.readline().split())) for _ in range(peo)]
maxx = sys.maxsize
check = [0] * peo

def dfs(num, cnt):
    global maxx
    if cnt == peo // 2:
        choice, non_choice = 0, 0
        for y in range(peo):
            for x in range(peo):
                if check[x] == 1 and check[y] == 1:
                    choice += box[y][x]
                elif check[x] == 0 and check[y] == 0:
                    non_choice += box[y][x]
        k = abs(choice - non_choice)
        if maxx > k:
            maxx =  k
    for x in range(num, peo):
        if check[x] == 0:
            check[x] = 1
            dfs(x + 1, cnt + 1)
            check[x] = 0
            # dfs(x + 1, cnt)

dfs(0, 0)
print(maxx)
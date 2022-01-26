import sys

T = int(sys.stdin.readline().strip())
for tc in range(1, T + 1):
    SPOT = list(map(int, sys.stdin.readline().strip().split()))
    N = int(sys.stdin.readline().strip())
    List = [list(map(int, sys.stdin.readline().strip().split())) for _ in range(N)]
    cnt = 0
    for x, y, r in List:
        now = 0
        if ((abs(SPOT[0] - x) ** 2) + (abs(SPOT[1] - y) ** 2)) < r ** 2:
            now += 1
        if ((abs(SPOT[2] - x) ** 2) + (abs(SPOT[3] - y) ** 2)) < r ** 2:
            now += 1
        if now == 1:
            cnt += 1
        
    print(cnt)
"""
cooker: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('cooker_input.txt')


def dfs(now, k):
    if now >= N //2:
        cooked.add(tuple(use))
        return

    for num in range(k, N):
        if use[num] == 0:
            use[num] = 1
            dfs(now+1, num + 1)
            use[num] = 0


def cook(using):
    global result
    total_a = 0
    total_b = 0
    for x in range(N):
        for y in range(x+1, N):
            if using[x] == 0 and using[y] == 0:
                total_a += MAP[x][y] + MAP[y][x]
            elif using[x] == 1 and using[y] == 1:
                total_b += MAP[x][y] + MAP[y][x]
    tmp = abs(total_a - total_b)
    if result > tmp:
        result = tmp

T = int(input())
for tc in range(1, T + 1):
    N =int(input())
    MAP = [list(map(int, input().rstrip().split())) for _ in range(N)]  
    cooked = set()
    use = [0] * N
    result = float('inf')
    dfs(0, 0)
    for tu in cooked:
        cook(tu)
        if result == 0:
            break
    print(f'#{tc} {result}')
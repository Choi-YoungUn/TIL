"""
low_cost: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('low_cost_input.txt')


def dfs(now, cost):
    global result
    if now >= N:
        if result > cost:
            result = cost
        return 

    if cost > result:
        return

    for next in range(N):
        if creat[next] == 0:
            creat[next] = 1
            dfs(now+1, cost + MAP[now][next])
            creat[next] = 0


T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input().strip())
    creat = [0] * (N+1)
    MAP = [list(map(int, input().split()))for _ in range(N)]
    result = float('inf')
    dfs(0,0)
    print(f'#{tc} {result}')
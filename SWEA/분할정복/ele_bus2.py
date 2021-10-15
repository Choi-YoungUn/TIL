"""
ele_bus2: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('ele_bus2_input.txt')


def dfs(now, cnt):
    global result
    if now >= N - 1:
        if result > cnt:
            result = cnt
        return

    if cnt > result:
        return

    for ex_gus in range(ins[now], 0, -1):
        visited[now] = 1
        dfs(now + ex_gus, cnt + 1)
        visited[now] = 0


T = int(input().strip())
for tc in range(1, T + 1):
    inputs = list(map(int, input().strip().split())) +[0]
    N = inputs[0]
    ins = inputs[1:]
    result = float('inf')
    visited = [0] * (N+1)
    dfs(0, 0)

    
    print(f'#{tc} {result -1}')

'''
# 전기버스2 (가지치기)
# 2가지 방법
# 1. dp
# 2. 가지치기

def dfs(now, cnt = -1):
    global ans
    # now : 현재 위치
    if cnt >= ans:
        return

    if now >= n - 1:
        ans = min(ans, cnt)
        return

    for next in range(now + 1, now + chs[now] + 1):
        dfs(next, cnt + 1)

t = int(input())
for tc in range(t):
    data = list(map(int, input().split()))
    n = data[0]
    chs =  data[1:]
    ans = 2134567890
    dfs(0)
    print(f"#{tc + 1} {ans}")

'''

'''
# 전기버스2(dp, for)

t = int(input())
for tc in range(t):
    data = list(map(int, input().split()))
    n = data[0]
    chs =  data[1:]
    dp = [2134567890] * (n + 100)
    dp[0] = 0
    for now in range(len(chs)):
        for next in range(now + 1, now + chs[now] + 1):
            dp[next] = min(dp[next], dp[now] + 1)

    print(f"#{tc + 1} {dp[n - 1] - 1}")
    '''
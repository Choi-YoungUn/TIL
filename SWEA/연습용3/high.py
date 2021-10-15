"""
high: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('high_input.txt')


def dfs(now, high):
    if now >= N:
        if B <= high:
            re_li.append(high)
        return
    
    if make[now] ==0 :
        make[now] = 1
        dfs(now+1, high + H[now])
        make[now] = 0
        dfs(now+1, high)

T = int(input().strip())

for tc in range(1, T + 1):
    N, B = map(int, input().split())
    H = list(map(int, input().split()))
    make = [0] * N
    re_li = []
    dfs(0,0)
    result = min(re_li)
    print(f'#{tc} {result -B}')

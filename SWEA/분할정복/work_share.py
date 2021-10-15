"""
work_share: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('work_share_input.txt')


def dfs(people, parsent):
    global result
    if people >= N:
        if result < parsent :
            result = parsent
        return
    
    if result >= parsent:
        return
    
    for works in range(N):
        if visited[works] == 0:
            visited[works] = 1
            dfs(people + 1, parsent * work[people][works] / 100)
            visited[works] = 0


T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input())
    work = [list(map(int, input().split())) for _ in range(N)]
    visited = [0] * N 
    result = 0.0
    
    dfs(0, 1)
    print(f'#{tc} {result * 100:.6f}')
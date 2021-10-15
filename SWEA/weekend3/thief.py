"""
thief: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('thief_input.txt')

from collections import deque
#후하좌상
di = [0, 1, 0, -1]
dj = [1, 0, -1, 0]
pipe = [
    [0, 0, 0, 0],
    [1, 1, 1, 1],
    [0, 1, 0, 1],
    [1, 0, 1, 0],
    [1, 0, 0, 1],
    [1, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 1]
]


T = int(input().strip())
for tc in range(1, T + 1):
    N, M, R, C, L = map(int, input().split())
    tunnel = [list(map(int, input().split()))for _ in range(N)]
    visited = [[0] * M for  _ in range(N)]
    Q = [(R, C)]
    visited[R][C] = 1
    result = 0

    while len(Q) > 0:
        r, c = Q.pop(0)
        result += 1
        if visited[r][c] >= L:
            continue
        for i in range(4):
            nr = r + di[i]
            nc = c + dj[i]

            if nr < 0 or nr >= N or nc < 0 or nc >= M:
                continue

            if pipe[tunnel[r][c]][i] == 0:
                continue

            nd = (i + 2) % 4
            np = tunnel[nr][nc]

            if visited[nr][nc] or pipe[np][nd] == 0:
                continue

            visited[nr][nc] = visited[r][c] + 1

            Q.append((nr, nc))

    print("#{} {}".format(tc, result))
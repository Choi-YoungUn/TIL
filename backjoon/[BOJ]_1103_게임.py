# 백준 게임 1103
import sys

sys.setrecursionlimit(int(1e7))

def dfs(row = 11, col = 11):
    global success
    if not success:
        # 불가능한 상태면 아무것도 하지 말고 끝내라
        return 0
    if MAP[row][col] == 0:
        # 구멍이거나 맵 밖으로 벗어났다.
        return 0
    if DP[row][col] != -1:
        # 기록된게 있으면
        return DP[row][col]

    dr = [-1,1,0,0]
    dc = [0,0,-1,1]
    ret = 0
    for i in range(4):
        next_row = row + dr[i] * MAP[row][col]
        next_col = col + dc[i] * MAP[row][col]
        if check[next_row][next_col] :
            # 이미 기록이 있으면 갔던 점을 다시 가는 것이니 사이클을 이루게 된다.
            success = False # 무한하게 반복하여 불가능한 상태
            return 0
        check[next_row][next_col] = True
        ret = max(ret, dfs(next_row, next_col) + 1)
        check[next_row][next_col] = False # 기록 삭제(다른 경로로도 갈 수 있도록 구성)
    DP[row][col] = ret
    return ret


H, W = map(int, sys.stdin.readline().split())
MAP = [[0] * (22 + W) for _ in range(22 + H)]
DP = [[-1] * (22 + W) for _ in range(22 + H)]
check = [[False] * (22 + W) for _ in range(22 + H)]
success = True
temp_MAP = [list(sys.stdin.readline()) for _ in range(H)]
for row in range(H):
    for col in range(W):
        if temp_MAP[row][col] == 'H':
            MAP[row + 11][col + 11] = 0
        else:
            MAP[row + 11][col + 11] = int(temp_MAP[row][col])

ans = dfs()
if success:
    print(ans)
else:
    print(-1)
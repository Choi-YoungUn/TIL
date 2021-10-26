# 돌다리 건너기 2602
import sys

# 반환 받는 구조

def dfs(row, col, cnt):
    if cnt >= len(op):
        return 1 # op를 모두 밟았으니 끝! (정상)
    if col >= 0 and DP[row][col][cnt] != -1:
        return DP[row][col][cnt]
    # cnt : 내가 이번에 밟아야 하는 op번호
    next_row = 1 - row  # row 1 -> 0, row 0 -> 1
    ret = 0
    for next_col in range(col + 1, len(MAP[next_row])):
        if MAP[next_row][next_col] == op[cnt]:
            ret += dfs(next_row, next_col, cnt + 1) # 다양한 방법으로 밟아본다.
            # 모든 방법을 누적
    DP[row][col][cnt] = ret
    return ret

op = sys.stdin.readline()
MAP = [sys.stdin.readline() for _ in range(2)]

DP = [[[-1] * len(op) for _ in range(len(MAP[0]))] for _ in range(2)]
# DP[row][col][cnt] <- row,col까지 왔고, 이제 cnt번째 op를 밟아야 한다. 그럴 때 마지막까지 몇 가지 방법이 가능한가?



print( dfs(0, -1, 0) + dfs(1, -1, 0) )
# dfs(0,-1,0) : 아직 아무것도 밟지 않은 상태로 '아랫칸'부터 밟기 시작
# dfs(1, -1, 0) : 아직 아무것도 밟지 않은 상태로 '윗칸'부터 밟기 시작
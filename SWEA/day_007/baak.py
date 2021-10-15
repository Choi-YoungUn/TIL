def color(n,k,answer):
    if(n/k == 2):
        return 2
    if(k == 1):
        return n
    if(answer[n][k] == 0):
        total = color(n-1,k,answer) + color(n-2,k-1,answer)
        answer[n][k] = total
        return total
    else:
        return answer[n][k]
        
n = int(input())
k = int(input())

answer = [[0]*(n+1) for i in range(n+1)]

if(n/2 < k):
    print(0)
else:
    print(color(n,k,answer)%1000000003)
###################################섬 탐색
def dfs (row, col): # now : row,col의 위치
    dr = [-1,1,0,0]
    dc = [0,0,-1,1]
    for i in range(4):
        next_row = row + dr[i]
        next_col = col + dc[i]
        # now -> next로 갈 수 있으면 가라!
        if next_row < 0 or next_col < 0 or next_row >= h or next_col >= w:
            continue
        if MAP[next_row][next_col] == 1 and visited[next_row][next_col] == 0:
            # 나랑 인접한 곳이 땅이다!
            visited[next_row][next_col] = 1
            dfs(next_row, next_col)

# 맵을 벗어나는 좌표가 계산

while True:
    w, h = map(int, input().split())
    if w == 0 and h == 0:
        break
    MAP = [ list(map(int, input().split())) for _ in range(h) ]
    visited = [[0] * w for _ in range(h)]
    # visited[row][col] <- 1 : row,col을 들린적있다. 0 : row, col를 들린적 없다.
    for i in range(h):
        for j in range(w):
            if MAP[i][j] == 1 and visited[i][j] == 0:
                visited[i][j] = 1
                dfs(i, j)
                de = 1
    # 가로크기 w, 세로크기 h

####################### 색상환!
N = int(input())
K = int(input())

dp = [[0] * (N + 1) for _ in range(N + 1)]

for i in range(N + 1):
    dp[i][0] = 1
    dp[i][1] = i

for i in range(2, N):
    # i : 이번까지 고려할 색 개수
    for j in range(2, K + 1):
        # j : i개의 색 중에서 고른 색의 수
        dp[i][j] = (dp[i - 2][j - 1] + dp[i - 1][j]) % 1000000003
        # 마지막에 추가된 i개째의 색을 고르는가
        # O : [i-2][j-1]
        # X : [i-1][j]
print( (dp[N-3][K-1] + dp[N-1][K]) % 1000000003 )
import sys

sys.setrecursionlimit(30000)# 재귀 횟수 제한 해제

# 입력
N, M = map(int, sys.stdin.readline().split())
MAP = []
visited = []  #방문했는지
for adds in range(N):     #맵핑하기
    box = sys.stdin.readline().strip()
    temp = []
    for add in box:
        temp.append(int(add))
    MAP.append(temp)
    visited.append([0] * M)
# 도착지를 설정해준다  최단 횟수를 기록해야하므로.
MAP[N - 1][M - 1] = 9999

#출발지로 되돌아오지않게 설정
visited[0][0] = 1

#지금 위치와 벽을 뚫었는지. 몇번째 이동인지를 받는다.
def go(now_x, now_y, dig_fleg, steps):
    #상하좌우
    di = [-1, 1, 0, 0]
    dj = [0, 0, -1, 1]

    global visited
    for move in range(4):
        #다음 좌표 설정
        next_x = now_x + di[move]
        next_y = now_y + dj[move]
        
        #좌표 유효성 검사
        if 0 <= next_x < N and 0 <= next_y < M:

            #다음좌표가 도착지라면!  기존 값과 현재 값(이동거리)를 비교해서 적은쪽을 적는다
            if next_x == N -1 and next_y == M - 1:
                MAP[N - 1][M - 1] = min(steps + 1, MAP[N - 1][M - 1])

            #다음 좌표가 0이며 방문하지 않은 곳이라면
            if MAP[next_x][next_y] == 0 and visited[next_x][next_y] == 0:
                #방문 했다고 표기
                visited[next_x][next_y] = 1
                #다음으로 진행! 벽은 뚫지 않았으니 그대로 이동, 걸음수 증가
                go(next_x, next_y, dig_fleg, steps + 1)
                #방문하지 않은 것으로 체크
                visited[next_x][next_y] = 0
            
            #다음좌표가 벽이지만 벽을 뚫을 수 있는 기회가 있으며 방문하지 않은 곳이었다면
            if MAP[next_x][next_y] == 1 and dig_fleg == 1 and visited[next_x][next_y] == 0:
                #방문한 것으로 표기
                visited[next_x][next_y] = 1
                #다음으로 이동. 이때 벽뚫기 사용을 표시 (0으로), 걸음수 증가
                go(next_x, next_y , 0, steps + 1)
                #방문하지 않은것으로 다시 표기.
                visited[next_x][next_y] = 0

#출발 좌표 x, y  ,  벽뚫기 사용가능여부, 걸음수.
go(0, 0, 1, 0)

#도착지의 값이 변했다면 
if MAP[N - 1][M - 1] != 9999:
    #걸음수 출력
    print(MAP[N - 1][M - 1] + 1)
else:
    #변하지 않았다면(도착할 수 없었다면) -1 출력
    print('-1')
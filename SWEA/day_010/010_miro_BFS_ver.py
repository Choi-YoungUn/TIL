"""
010_miro_BFS_ver: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('010_miro_BFS_ver_input.txt')

# BFS
T = int(input())
for tc in range(T):
    N = int(input())
    # 1. 연결 구조를 구성
    MAP = [ list(map(int, input().rstrip())) for _ in range(N) ]
    visited = [ [0] * N for _ in range(N) ]
    result = 0
    # 2. queue 생성(append, pop활용 version)
    q = []

    # 3. 시작점 세팅(시작점을 queue에 추가)
    for row in range(N):
        for col in range(N):
            if MAP[row][col] == 2:
                # 시작점도 찾은거나 다름없으니 기록
                visited[row][col] = 1
                q.append([row, col])
    while len(q) !=0 and result == 0:
        # 4. queue에서 맨 앞 점를 꺼냄(now)
        # ---- 추가적인 계산이 필요한 경우 여기서
        now = q.pop(0)
        now_row = now[0]
        now_col = now[1]

        # 5. now에서 갈 수 있는 모든 점을 찾기(next)
        dr = [-1,1,0,0]
        dc = [0,0,-1,1]
        for i in range(4):
            next_row = now_row + dr[i]
            next_col = now_col + dc[i]
            # ----안되는것 검사-----
            if next_row < 0 or next_col < 0 or next_row >= N or next_col >= N:
                continue #맵을 벗어나는 문제, 무시
            if MAP[next_row][next_col] == 1:
                continue #next가 벽이면 무시
            if visited[next_row][next_col] == 1:
                continue # 찾았던 점이면 무시
            # --------------------
            #6. next를 queue에 넣기
            # ---- 추가적인 계산이 필요한 경우 여기서
            if MAP[next_row][next_col] == 3:
                result = 1
                break
            visited[next_row][next_col] =  1
            # 찾았다라고 기록
            q.append([next_row, next_col])
    print("#{} {}".format(tc, result))


    """
1. 연결 구조를 구성
2. queue 생성
3. 시작점 세팅
----준비---
4. queue에서 맨 앞 점를 꺼냄(now)
5. now에서 갈 수 있는 모든 점을 찾기(next)
6. next를 queue에 넣기
7. 4~6번 단계를 queue가 비워질 때까지
    
--- 기본 구성 완료 ----
옵션 : 
1. 맵을 벗어나는가? : 2차원맵 한정
2. 갈 수 없는 점 확인
3. 갔던 점을 다시 돌아갈 수 있는가? <- visited배열 활용
   visited : 내가 찾은 점인가?
   
---- 살짝 응용 ----
1. 몇 번 만에 갈 수 있는가?
   visited : 내가 몇 번만에 찾은 점인가?
   
실제 BFS가 어디서 활용되느냐!!!!!!!!
1. 제일 적게 다른 점을 들려서 가는 방법
    -BFS에서 어떤 점을 발견하면 그 점이 가장 빠른 타이밍에 발견 된 것이다.

    """
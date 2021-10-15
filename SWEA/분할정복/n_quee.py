"""
n_quee: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('n_quee_input.txt')


def dfs(now):
    global result
    if now == N:
        result += 1
        return
    
    for point in range(N):
        if y_check[point] == 1:
            continue
        x_check[now] = point

        if check(now):
            continue

        y_check[point] = 1
        dfs(now + 1)
        y_check[point] = 0


def check(num):                
    for i in range(num):
        if abs(x_check[num] - x_check[i]) == num - i:
            return True
    return False


T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input())
    x_check = [0] * N
    y_check = [0] * N
    result = 0
    dfs(0)
    print(f'#{tc} {result}')




#1. 숫자 입력
#2. 보드만들기
#3. 놨을 경우 안놨을 경우 생각하기.

'''
# N Queen
def dfs(now):
    # now번째 줄에 말을 배치한다.
    if now >= N:
        # 맨 끝줄까지 말을 배치했다.
        # 가지치기를 모두 통과하여 '정상적인'상태이다.
        global ans
        ans += 1
        print(f"------{ans}------")
        for row_MAP in MAP:
            print(row_MAP)
        print()
        return

    for col in range(N):
        if check_col[col] : # 이 열은 앞에서 사용 중이다.
            continue #가지치기
        if check_ru_ld[now + col]:# 이 대각선은 앞에서 사용 중이다.
            continue #가지치기
        if check_lu_rd[now - col]:# 이 대각선은 앞에서 사용 중이다.
            continue #가지치기
            
        check_col[col] = True
        check_ru_ld[now + col] = True  # 오른쪽위->왼쪽아래 대각선은 row+col으로 계산하여 번호를 매겨줄 수 있다.
        check_lu_rd[now - col] = True  # 왼쪽위->오른쪽아래 대각선은 row-col으로 계산하여 번호를 매겨줄 수 있다.
        MAP[now][col] = 1
        dfs(now + 1)
        # 다음줄로 넘어가라
        MAP[now][col] = 0
        # col위치에 두는 방법은 다 해봤으니 기록을 삭제
        check_col[col] = False # 기록 복구
        check_ru_ld[now + col] = False
        check_lu_rd[now - col] = False

N = int(input())
check_col = [False] * N # 어떤 열을 사용했는가?
check_ru_ld = [False] * ( 2*N + 1) # 어떤 대각선(오른쪽위 -> 왼쪽아래)을 사용했는가?
check_lu_rd = [False] * ( 2*N + 1) # 어떤 대각선(왼쪽위 -> 오른쪽아래)을 사용했는가?
ans = 0
MAP = [[0] * (N) for _ in range(N)]
dfs(0)
'''
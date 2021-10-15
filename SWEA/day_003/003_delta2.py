"""
003_delta2: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('003_delta2_input.txt')

T = 10
for tc in range(T):
    N = int(input())
    num = []
    num = [ list(map(int, input().split())) for _ in range(N) ]

    sum = 0
    for row in range(N):
        for col in range(N):
            # num[row][col]
            
            dr = [-1, -2, -2, -1, 1, 2, 2, 1]
            dc = [-2, -1, 1, 2, 2, 1, -1, -2]
            for i in range(8):
                nr = row + dr[i]
                nc = col + dc[i]
                
                if nr < 0 or nc < 0 or nr >= N or nc >= N :
                    continue
                
                # 우리가 원하는 범위 내에 있는가?

                # nr, nc : 다음 좌표(인접한 좌표)
                diff = num[row][col] - num[nr][nc]
                if (diff < 0): # 절대값
                    diff *= -1
                sum += diff
    print("#{} {}".format(tc + 1, sum))
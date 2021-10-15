"""
004_where: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('004_where_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    nk = list(map(int,input().split()))
    temp = []
    for x in range(nk[0]):
        temp.append(list(map(int,input().split())))
    
    counts = 0
    for x in range(nk[0]):
        x_count = []
        y_count = []
        temp_num_x = 0
        temp_num_y = 0
        for y in range(nk[0]):
            
            if temp[x][y] == 1:
                temp_num_x += 1
            else:
                x_count.append(temp_num_x)
                temp_num_x = 0

            if temp[y][x] == 1:
                temp_num_y += 1
            else:
                y_count.append(temp_num_y)
                temp_num_y = 0
        else:
            x_count.append(temp_num_x)
            y_count.append(temp_num_y)
            for check in range(len(x_count)):
                if nk[1] == x_count[check]:
                    counts += 1
            
            for check in range(len(y_count)):
                if nk[1] == y_count[check]:
                    counts += 1

    print("#{} {}".format(test_case, counts))

# T = int(input())
# for tc in range(T):
#     N, K = map(int, input().split())
#     MAP = [list(map(int, input().split())) for _ in range(N)]
#     ans = 0
#     # 가로
#     for row in range(N):
#         length = 0
#         for col in range(N):
#             if MAP[row][col] == 1:
#                 length += 1
#                 if col + 1 == N or MAP[row][col + 1] == 0:
#                 # 뒤에가 벽인가? : 단어의 끝인가
#                     if length == K: # 단어의 길이가 K
#                         ans += 1
#             else :
#                 length = 0

#     # 세로
#     for col in range(N):
#         length = 0
#         for row in range(N):
#             if MAP[row][col] == 1:
#                 length += 1
#                 if row + 1 == N or MAP[row + 1][col] == 0:
#                     if length == K:
#                         ans += 1
#             else :
#                 length = 0
#     print("#{} {}".format(tc + 1, ans))
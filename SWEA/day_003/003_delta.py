"""
003_delta: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('003_delta_input.txt')

def my_abs(num):
    if num == 0:
        return 0
    elif num > 0:
        return num
    elif num < 0:
        return -num

T = 10
for test_case in range(1, T + 1):
    n = int(input())
    box = []
    result_list = []
    result = 0
    for x in range(n):
        box.append(list(map(int, input().split())))
        result_list.append([0]* n)
    
    for i in range(n):
        for j in range(n):
            temp_x = 0
            temp_y = 0
            if i == 0:
                temp_y = my_abs(box[i + 1][j] - box[i][j])
            elif i == (n-1):
                temp_y = my_abs(box[i - 1][j] - box[i][j])
            else:
                temp_y = my_abs(box[i + 1][j] - box[i][j]) + my_abs(box[i - 1][j] - box[i][j])
            
            if j == 0:
                temp_x = my_abs(box[i][j + 1] - box[i][j])
            elif j == (n-1):
                temp_x = my_abs(box[i][j - 1] - box[i][j])
            else:
                temp_x = my_abs(box[i][j + 1] - box[i][j]) + my_abs(box[i][j - 1] - box[i][j])
            result += temp_x + temp_y
            result_list[i][j] = temp_x + temp_y
    print("#%d %d" %(test_case , result))



# T = 10
# for tc in range(T):
#     N = int(input())
#     num = []
#     """
#     for i in range(N):
#         num += [list(map(int, input().split()))]
#         # num.append(list(map(int, input().split())))
#     """
#     num = [ list(map(int, input().split())) for _ in range(N) ]

#     sum = 0
#     for row in range(N):
#         for col in range(N):
#             num[row][col]
#             #     상,하,좌,우
#             dr = [-1, 1, 0, 0]
#             dc = [ 0, 0,-1, 1]
#             for i in range(4):
#                 nr = row + dr[i]
#                 nc = col + dc[i]
#                 """
#                 if nr < 0 or nc < 0 or nr >= N or nc >= N :
#                     continue
#                 """
#                 # 우리가 원하는 범위 내에 있는가?

#                 # nr, nc : 다음 좌표(인접한 좌표)
#                 diff = num[row][col] - num[nr][nc]
#                 if (diff < 0): # 절대값
#                     diff *= -1
#                 sum += diff
#     print("#{} {}".format(tc + 1, sum))
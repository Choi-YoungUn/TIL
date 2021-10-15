"""
004_color: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('004_color_input.txt')

T = int(input())
# T = 3
for test_case in range(1, T + 1):
    num = int(input())
    paper = []
    white_paper = []
    purple = 0
    for x in range(10):
        white_paper.append([0] * 10)
    for x in range(num):
        paper.append(list(map(int,input().split())))

    for x in range(num):
        for i in range(paper[x][1], paper[x][3] + 1):
            for j in range(paper[x][0], paper[x][2] + 1):
                if white_paper[i][j] < 3 and white_paper[i][j] != paper[x][4]:
                    white_paper[i][j] += paper[x][4]
                    if white_paper[i][j] == 3:
                        purple += 1

    print("#{} {}".format(test_case + 1, purple))


# T = int(input())
# for tc in range(T):
#     N = int(input())
#     red = []
#     blue = []
#     for i in range(N):
#         box = list(map(int, input().split()))
#         if box[-1] == 1:
#             red += [box]
#         if box[-1] == 2:
#             blue += [box]
#     # box
#     # r1, c1, r2, c2
#     # 왼쪽 위, 오른쪽 아래
#     # min_r,min_c,max_r,max_c
# #index: 0,  1,     2,   3
#     ans = 0
#     # 칼라별 box 1개씩 고르기
#     for now_red in red:
#         for now_blue in blue:
#             # 겹치지 않는지 확인, 겹치지 않는다면 무시
#             if now_red[2] < now_blue[0] or now_blue[2] < now_red[0] :
#                 continue
#             if now_red[3] < now_red[1] or now_blue[3] < now_red[1] :
#                 continue

#             pu_min_row = 0
#             if now_red[0] < now_blue[0]: # min_row끼리 비교
#                 pu_min_row = now_blue[0] # 둘 중 큰쪽
#             else :
#                 pu_min_row = now_red[0]

#             pu_min_col = 0
#             if now_red[1] < now_blue[1]: # min_col끼리 비교
#                 pu_min_col = now_blue[1] # 둘 중 큰쪽
#             else :
#                 pu_min_col = now_red[1]

#             pu_max_row = 0
#             if now_red[2] < now_blue[2]: # max_row끼리 비교
#                 pu_max_row = now_red[2] # 둘 중 작은 쪽
#             else :
#                 pu_max_row = now_blue[2]

#             pu_max_col = 0
#             if now_red[3] < now_blue[3]: # max_col끼리 비교
#                 pu_max_col = now_red[3] # 둘 중 작은 쪽
#             else :
#                 pu_max_col = now_blue[3]
#             #보라색 넓이 = 가로길이               *      세로 길이
#             now_pu = (pu_max_col - pu_min_col + 1) * (pu_max_row - pu_min_row + 1)
#             ans += now_pu
#     print("#{} {}".format(tc + 1, ans))
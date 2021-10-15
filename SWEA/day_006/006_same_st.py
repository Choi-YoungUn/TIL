"""
006_same_st: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('006_same_st_input.txt')




T = int(input())
for test_case in range(1, T+ 1):
    nm = list(map(int, input().split()))
    box_x =[]
    for x in range(nm[0]):
        box_x.append(list(input()))

    for x in range(nm[0]):
        temp = []
        for y in range(nm[0]):
            temp.append(box_x[y][x])
        box_x.append(temp)
    result = ''
    for k in range(len(box_x)):
        for x in range(nm[0] - nm[1] + 1):
            for y in range(nm[0] // 2):
                de = box_x[k][x + y]
                dee = box_x[k][x + nm[1] - y -1]
                if box_x[k][x + y] != box_x[k][x + nm[1] - y -1]:
                    break
            else:
                result = ''.join(box_x[k][x : x + nm[1]])
        if result != '':
            break
    print("#{} {}".format(test_case , result))


# ### 1
# T = int(input())
# for tc in range(T):
#     N, M = map(int, input().split())
#     str_list = [input() for _ in range(N)]
#     for i in range(N):
#         # i : 가로 기준점
#         temp = ""
#         for j in range(N):
#             # j : 세로 줄 번호
#             temp += str_list[j][i]
#         str_list.append(temp)
#     ans = ""
#     for str_temp in str_list:
#         for i in range(N - M + 1):
#             temp = str_temp[i:i + M] # i~i+M-1 <- M개의 길이 문자열
#             #회문 : 앞에서 부터 읽은 문자열 == 뒤에서 부터 읽은 문자열
#             cnt = 0
#             for j in range(len(temp) // 2):
#                 if temp[j] == temp[len(temp) -1 -j]:
#                     cnt += 1
#             if cnt == len(temp) // 2:
#                 ans = temp
#             """
#             if temp == temp[::-1]:
#                 ans = temp
#             """
#     print("#{} {}".format(tc + 1, ans))

# ### 2회문 세로 처리 없이 계산
# T = int(input())
# for tc in range(T):
#     N, M = map(int, input().split())
#     str_list = [input() for _ in range(N)]
#     ans = ""
#     for row in range(len(str_list)):
#         for col in range(N - M + 1):
#             temp = str_list[row][col:col + M] # i~i+M-1 <- M개의 길이 문자열
#             #회문 : 앞에서 부터 읽은 문자열 == 뒤에서 부터 읽은 문자열
#             cnt = 0
#             for j in range(len(temp) // 2):
#                 if temp[j] == temp[len(temp) -1 -j]:
#                     cnt += 1
#             if cnt == len(temp) // 2:
#                 ans = temp

#         for col in range(N - M + 1):
#             #회문 : 앞에서 부터 읽은 문자열 == 뒤에서 부터 읽은 문자열
#             cnt = 0
#             for j in range(M // 2):
#                 if str_list[col + j][row] == str_list[col + M - 1 - j][row]:
#                     cnt += 1
#             if cnt == M // 2:
#                 ans = ""
#                 for j in range(M):
#                     ans += str_list[col + j][row]

#     print("#{} {}".format(tc + 1, ans))
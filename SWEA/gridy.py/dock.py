"""
dock: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('dock_input.txt')


# def dfs(bef_time, cnt):
#     global result
#     for st_time, end_time in time_list:
#         if bef_time <= st_time:
#             if result < cnt:
#                 result = cnt
#             dfs(end_time, cnt + 1)


T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input().strip())
    time_list = [list(map(int, input().strip().split()))for _ in range(N)]

    time_list.sort(key=lambda a: a[1])
    bef_time = 0
    result = 0

    for st_time, end_time in time_list:
        if bef_time <= st_time:
            result += 1
            bef_time = end_time

    print('#{} {}'.format(tc, result))
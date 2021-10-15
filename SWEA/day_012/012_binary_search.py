"""
012_binary_search: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('012_binary_search_input.txt')


def tree(now):
    global cnt
    if now <= N:
        tree(now * 2)
        temp[now] = cnt
        cnt += 1
        tree(now*2 + 1)

T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input().strip())
    temp = [0] * (N + 1)
    cnt = 1
    tree(1)
    # print(cnt)
    print("#{} {} {}".format(tc, temp[1], temp[N//2]))

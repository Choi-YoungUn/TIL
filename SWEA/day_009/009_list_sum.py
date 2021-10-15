"""
009_list_sum: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('009_list_sum_input.txt')

def go(line_j, sums):
    global minn
    if len(stack_line) == N and sums < minn:
        minn = sums

    for i in range(N):
        if i not in stack_line:
            if sums + maps[i][line_j] > minn:
                continue
            stack_line.append(i)
            go(line_j + 1, sums + maps[i][line_j])
            stack_line.pop(-1)

T = int(input())
for tc in range(1, T + 1):
    N = int(input())
    maps = [list(map(int, input().split())) for _ in range(N)]
    stack_line = []
    minn = 10 * N
    go(0, 0)
    print("#{} {}".format(tc, minn))
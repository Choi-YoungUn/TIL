"""
009_miro: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('009_miro_input.txt')

def go(now_i, now_j):
    global result
    di = [-1, 1, 0, 0]
    dj = [0, 0, -1, 1]
    
    for x in range(4):
        next_i = now_i + di[x]
        next_j = now_j + dj[x]
        if 0 <= next_i <= N - 1 and 0 <= next_j <= N - 1:
            if  miro[next_i][next_j] == 3:
                result = 1
                return
            elif miro[next_i][next_j] == 0:
                miro[next_i][next_j] = 1
                go(next_i, next_j)
                miro[next_i][next_j] = 0

T = int(input())
for tc in range(1, T + 1):
    N = int(input())
    miro = []
    for x in range(N):
        temp = input().strip()
        temp2 = []
        for y in range(len(temp)):
            temp2.append(int(temp[y]))
        miro.append(temp2)
    result = 0
    start_i = 0
    start_j = 0
    for i in range(N):
        for j in range(N):
            if miro[i][j] == 2:
                start_i = i
                start_j = j
                break
    go(start_i, start_j)
    print("#{} {}".format(tc, result))
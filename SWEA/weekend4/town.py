"""
town: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('town_input.txt')

def Find(num):
    if num == root[num]:
        return num

    px = Find(root[num])
    root[num] = px
    return px

def union(num1, num2):
    px = Find(num1)
    py = Find(num2)
    if px == py:
        return
    root[py] = px


T = int(input())
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    root = [x for x in range(N+1)]
    result = set()
    for _ in range(M):
        N1, N2 = map(int, input().split())
        union(N1, N2)
    for x in range(N+1):
        Find(x)
        result.add(root[x])
    print(f'#{tc} {len(result) -1}')
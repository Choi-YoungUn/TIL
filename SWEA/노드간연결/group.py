"""
group: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('group_input.txt')


def Find(num):
    if num == node[num]:
        return num

    px = Find(node[num])
    node[num] = px
    return  px


def union(num1, num2):
    px = Find(num1)
    py = Find(num2)
    if px == py:
        return
    node[px] = py


T = int(input())
for tc in range(1, T +1):
    N, M = map(int, input().split())
    lists = list(map(int, input().split()))
    node = [x for x in range(N+1)]
    for index in range(0, len(lists), 2):
        union(lists[index], lists[index+1])
    tmp = set()
    
    
    for x in range(N+1):
        Find(x)
        tmp.add(node[x])
    print(f'#{tc} {len(tmp)-1}')
"""
012_tree: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('012_tree_input.txt')

def dfs(now):
    global count
    count += 1
    for next in temp[now]:
        dfs(next)

T = int(sys.stdin.readline().strip())
for tc in range(1, T + 1):
    E, N = map(int, sys.stdin.readline().split())
    node_li = list(map(int, sys.stdin.readline().split()))
    temp = [ [ ] for _ in range(E + 2)]
    for x in range(E):
        temp[node_li[x * 2]].append(node_li[x * 2 + 1])

    count = 0
    dfs(N)
    
    print("#{} {}".format(tc, count))

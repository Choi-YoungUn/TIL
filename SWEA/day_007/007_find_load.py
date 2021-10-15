"""
007_find_load: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('007_find_load_input.txt')


def dfs(now): 
    for to in range(100):
        if nodes[now][to] == 1 and visited[to] == 0:
            visited[to] = 1 
            if visited[99] == 1 :
                break
            dfs(to) 

T = 10
for test_case in range(1, T + 1):
    tc, counts = map(int, input().split())
    nodes_input = list(map(int, input().split()))
    visited = [0] * 100
    nodes = [[0] * 100 for _ in range(100)]
    for x in range(0, counts * 2 , 2):
        nodes[nodes_input[x]][nodes_input[x + 1]] = 1
    visited[0] = 1
    
    dfs(0)
    print("#{} {}".format(tc + 1, visited[99]))
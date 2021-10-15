"""
011_binary_tree_befor: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('011_binary_tree_befor_input.txt')

def in_traverse(T):
    global result
    
    if nodes[T * 2] != 0:
        in_traverse(nodes[T * 2] )
    result.append(nodes_alpa[T])
    if nodes[T * 2 + 1] != 0:
        in_traverse(nodes[T * 2 + 1])

for tc in range(1, 11):
    N = int(input())
    inputs = [list(map(str, input().split()))for _ in range(N)]
    temp_node = []
    nodes = [0] * ((N + 1) * 2)
    nodes_alpa = [0] * (N + 1)
    result = []
    for x in range(N):
        if len(inputs[x]) >= 3:
            temp_node.append([int(inputs[x][0]), int(inputs[x][2])])
        if len(inputs[x]) >= 4:
            temp_node.append([int(inputs[x][0]), int(inputs[x][3])])
        nodes_alpa[x + 1] = inputs[x][1]

    for i in range(N - 1):
        a, b = temp_node[i][0], temp_node[i][1]
        if nodes[a * 2] == 0:
            nodes[a * 2] = b
        else:
            nodes[a * 2 + 1] = b
    in_traverse(1)
    re_st = ''.join(result)
    print("#{} {}".format(tc, re_st))
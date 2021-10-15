"""
011_binary_tree: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('011_binary_tree_input.txt', 'rt', encoding='UTF8')

def preorder_traverse(T):
    global result
    result += str(T)+ ' '
    if G[T * 2] != 0:
        preorder_traverse(G[T * 2] )
    if G[T * 2 + 1] != 0:
        preorder_traverse(G[T * 2 + 1])



T = int(input())
for tc in range(1, T + 1):
    N = int(input().replace('\u200b', ''))
    G = [0] * ((N + 1) * 2) #한 노드에 두개씩 자식노드가 생길수 있으므로 

    result = ''
    for i in range(N - 1):
        a, b = map(int, input().split())
        if G[a * 2] == 0:
            G[a * 2] = b
        else:
            G[a * 2 + 1] = b
    preorder_traverse(1)
    print("#{} {}".format(tc, result.strip()))
    
    
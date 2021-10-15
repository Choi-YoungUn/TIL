"""
012_binary_hip: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('012_binary_hip_input.txt')

sys.setrecursionlimit(100000)

import heapq
T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input())
    NS = list(map(int, input().split()))
    tree = [] 
    for x in range(len(NS)):
        heapq.heappush(tree, NS[x])
        
    k = len(tree)
    cnt = 0
    while k > 1:
        k = k // 2
        cnt += tree[k-1]
    
    print("#{} {}".format(tc, cnt))


#     import heapq

# def insert(value): # heap구조로 node에 value를 추가
#     # 1. 일단 맨 뒤에 data(value)를 추가
#     node.append(value)
#     pos = len(node) - 1
#     # 2. 이번에 추가한 얘가 올바른 위치가 될 때까지 부모랑 swap
#     while pos != 0 and node[pos // 2] > node[pos]:
#         node[pos//2], node[pos] = node[pos], node[pos//2] # 부모랑 swap
#         pos //= 2 # 부모 위치로 이동했다고 갱신

# T = int(input())
# for tc in range(T):
#     N = int(input())
#     data = list(map(int, input().split()))
#     node = [0] # 완전 2진트리 N + 1
#     for i in data:
#         insert(i)
#     ans = 0
#     now = (len(node) - 1) // 2
#     while now != 0:
#         ans += node[now]
#         now //= 2
#     print(ans)
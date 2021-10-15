"""
008_sum: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('008_sum_input.txt')

# T = int(input())

# for tc in range(T):
#     N, K = map(int, input().split())

#     ans = 0
#     path = [-1] * 21
#     # 내가 어떻게 해왔는가? 를 기록
#     # -1 : 확인 안됨, 0 : 사용 X, 1 : 사용 O
#     def dfs(now, sum, cnt):
#         # now : 이번에 확인할 값,
#         # sum : 지금까지 만들어온 값,
#         # cnt : 지금까지 사용한 값의 개수
#         if now >= 21:
#             # 기저조건 : 끝날 조건
#             # '가지치기를 통과해서 끝까지 잘 도착했다' : 정답의 가능성이 있다.
#             #---- 정확히 N개의 개수로 합이 K가 되는가?
#             if sum == K and cnt == N:
#                 global ans
#                 ans += 1
#             return

#         # 사용한 경우
#         if sum + now <= K and cnt < N: # 가지치기
#             # k : 합, N : 개수
#             path[now] = 1 # now를 사용했다라고 기록
#             dfs(now + 1, sum + now, cnt + 1)

#         #사용하지 X
#         path[now] = 0 # now를 사용하지 않는다고 기록
#         dfs(now + 1, sum, cnt)

#         path[now] = -1 # now가 끝나서 초기값으로 되돌려 놓음

#     dfs(1,0,0)
#     print("#{} {}".format(tc + 1, ans))

def check(num = 1, sum = 0, cnt = 0):
    global N, K, result
    if num >= 21:
        if sum == K and cnt == N:
            result += 1
        return
    if sum + num <= K and cnt <= N:
        check(num + 1, sum + num, cnt + 1)
    check(num + 1, sum, cnt)

T = int(input())

for tc in range(T):
    N, K = map(int, input().split())
    result = 0
    check()
    print("#{} {}".format(tc + 1, result))
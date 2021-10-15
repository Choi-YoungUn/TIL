"""
010_pizza: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('010_pizza_input.txt')

T = int(input())
for tc in range(1, T + 1):
    N, M = map(int,input().split())
    pizza = list(map(int,input().split()))
    Q = [] 
    for x in range(N):
        Q.append([pizza[x], x])

    end_pi = 0
    while len(Q) != 1:
        Q[0][0] //= 2
        if Q[0][0] == 0 and N + end_pi < M:
            Q.pop(0)
            Q.append([pizza[N + end_pi], N + end_pi])
            end_pi += 1
        elif Q[0][0] == 0:
            Q.pop(0)
        else:
            Q.append(Q.pop(0))
    print('#{} {}'.format(tc, Q[0][1] + 1))
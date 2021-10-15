"""
birthday: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('birthday_input.txt')


from collections import deque
T = int(input())
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    both = [[0] * (N+1) for _ in range(N+1)]
    people = [0] * (N+1)
    for _ in range(M):
        a, b = map(int, input().split())
        both[a][b] = 1
        both[b][a] = 1
    q = deque()
    q.append((1, 0))
    people[1] = 1
    
    while q :
        now = q.popleft()
        now_peo = now[0]
        cnt = now[1]
        if cnt == 2:
            continue
        
        for x in range(N+1):
            if both[now_peo][x] == 1 and people[x] == 0:
                people[x] = 1
                q.append((x, cnt+1))
        
    result = people.count(1) -1
        
    # print(people)
    print(f'#{tc} {result}')
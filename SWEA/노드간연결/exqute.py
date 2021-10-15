"""
exqute: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('exqute_input.txt')


from collections import deque

#1 입력받기
T = int(input())
for tc in range(1, T +1):
    start_num, end_num = map(int, input().split())
    result = float('inf')
    tmp = deque()
    tmp.append((start_num, 0))
    visited = [-1] * (1000000+1)
    visited[start_num] = 1
    while tmp:
        
        now = tmp.popleft()
        now_num = now[0]
        cnt = now[1] +1

        num = now_num + 1
        if num == end_num:
            if cnt < result:
                result = cnt
            break
        if 0 < num <= 1000000:
            if visited[num] == -1 or visited[num] > cnt:
                visited[num] = cnt
                tmp.append((num, cnt))

        num = now_num - 1
        if num == end_num:
            if cnt < result:
                result = cnt
            break
        if 0 < num <= 1000000:
            if visited[num] == -1 or visited[num] > cnt:
                visited[num] = cnt
                tmp.append((num, cnt))

        num = now_num * 2
        if num == end_num:
            if cnt < result:
                result = cnt
            break
        if 0 < num <= 1000000:
            if visited[num] == -1 or visited[num] > cnt:
                visited[num] = cnt
                tmp.append((num, cnt))

        num = now_num - 10
        if num == end_num:
            if cnt < result:
                result = cnt
            break
        if 0 < num <= 1000000:
            if visited[num] == -1 or visited[num] > cnt:
                visited[num] = cnt
                tmp.append((num, cnt))
    
    print(f'#{tc} {result}')
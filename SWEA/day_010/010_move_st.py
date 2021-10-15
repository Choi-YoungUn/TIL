"""
010_move_st: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('010_move_st_input.txt')

T = int(input())
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    st_list = list(map(int, input().split()))
   
    for x in range(M):
        temp = st_list[0]
        st_list[:-1] = st_list[1:]
        st_list[-1] = temp
    print("#{} {}".format(tc, st_list[0]))


# def ADD(value):
#     global end
#     q[end] = value
#     end += 1
#     end %= len(q)
# def POP():
#     global front
#     global end
#     if front == end: # 비어있으면 못 꺼냄
#         return "error"
#     temp = q[front]
#     front += 1
#     front %= len(q)
#     return temp

# T = int(input())
# for tc in range(T):
#     N, M = map(int, input().split())
#     q = list(map(int, input().split())) + [0]
#     # queue의 크기는 항상 최대 넣을 데이터보다 1개 이상 더 커야합니다.
#     # 꽉차있는 것과 비어있는 것을 구분하기 위해
    
#     front = 0
#     end = len(q) - 1

#     for _ in range(M):
#         temp = POP()
#         ADD(temp)
#     print("#{} {}".format(tc + 1, POP()))
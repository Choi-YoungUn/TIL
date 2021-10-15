"""
move_con: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('move_con_input.txt')

T = int(input().strip())
for tc in range(1, T + 1):
    N, M = map(int, input().strip().split())
    box = list(map(int, input().strip().split()))
    truck = list(map(int, input().strip().split()))

    box.sort(reverse=True)
    truck.sort(reverse=True)
    result = 0
    for pick_truck in truck:
        for pick_box in range(len(box)):
            if pick_truck >= box[pick_box]:
                result += box[pick_box]
                box[pick_box] = float('inf')
                break
    print('#{} {}'.format(tc, result))

######### 컨테이너 운반

# t = int(input())
# for tc in range(t):
#     n, m = map(int, input().split())
#     weight = list(map(int, input().split()))
#     truck = list(map(int, input().split()))
#     weight.sort(reverse = True)
#     truck.sort(reverse = True)
#     # sort 시간 복잡도 nlogn

#     w_idx = 0 # 화물 index
#     t_idx = 0 # 트럭 index
#     ans = 0 # 실은 화물들의 무게

#     # 제일 용량이 큰 트럭           1개당
#         # 제일 용량이 큰 화물    n개의 화물
#                         #총 O(m * n)

#     while w_idx < n and t_idx < m:
#         if weight[w_idx] <= truck[t_idx]:
#             # 화물을 실을 수 있음
#             ans += weight[w_idx]
#             t_idx += 1
#         w_idx += 1

#     print(f"#{tc + 1} {ans}")
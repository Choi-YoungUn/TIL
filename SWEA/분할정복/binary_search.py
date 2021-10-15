"""
binary_search: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('binary_search_input.txt')




T = int(input().strip())
for tc in range(1, T + 1):
    N, M = map(int, input().strip().split())
    N_list = sorted(list(map(int,input().split())))
    M_list = list(map(int,input().split()))
    result = 0
    for tg in M_list:
        start = 0
        end = len(N_list)-1
        flag = 0
        while start <= end:
            mid =(start + end) //2
            if N_list[mid] == tg:
                result += 1
                break
            elif N_list[mid] < tg:
                if flag == 1:
                    break
                flag = 1
                start = mid + 1
            elif N_list[mid] > tg:
                if flag == 2:
                    break
                flag = 2
                end = mid - 1
            
        
    print(f'#{tc} {result}')



    #######################
    # 이진 탐색

# def binary_search(A, value):
#     # A라는 배열에서 value를 찾아라
#     l = 0
#     r = len(A) - 1
#     flag = 1
#     # 1 : 아직 아무것도 안고른 상태
#     # 0 : 왼쪽 구간을 고른 상태
#     # 2 : 오른쪽 구간을 고른 상태

#     # l~r
#     while l <= r: # 범위가 정상적이라면
#         mid = (l + r) // 2 # 하나를 예상해서 골라준다.
#         if A[mid] < value and flag <= 1: # 고른얘가 찾고자 하는 값보다 작으면 찾을 값은 더 오른쪽에 있다.
#             l = mid + 1
#             flag = 2
#         elif A[mid] > value and flag >= 1: # 고른얘가 찾고자 하는 값보다 크면 찾을 값이 더 왼쪽에 있다.
#             r = mid - 1
#             flag = 0
#         elif A[mid] == value: # 완벽하게 일치한다.
#             return True
#         else : # 앞에서 고른 구간을 또 고른 상태
#             return False
#     return False


# t = int(input())
# for tc in range(t):
#     n, m = map(int, input().split())
#     A = list(map(int, input().split()))
#     B = list(map(int, input().split()))

#     A.sort()
#     ans = 0
#     for value in B:
#         if binary_search(A, value):
#             ans += 1
#     print(f"#{tc + 1} {ans}")
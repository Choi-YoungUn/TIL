"""
004_po_sort: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('004_po_sort_input.txt')

# T = int(input())
# for test_case in range(1, T + 1):
#     num = int(input())
#     arr = list(map(int,input().split()))

#     lists_len = len(arr)
#     end = len(arr) - 1
#     while end > 0:
#         last_swap = 0
#         for i in range(end):
#             if arr[i] > arr[i + 1]:
#                 arr[i], arr[i + 1] = arr[i + 1], arr[i]
#                 last_swap = i
#         end = last_swap
#     temp =[]
#     counts = 1
#     while len(arr) > 0 and counts < 11:
        
#         if counts % 2 :
#             temp.append(str(arr.pop(-1)))
#         else:
#             temp.append(str(arr.pop(0)))
#         counts += 1
#     st = ' '.join(temp)
#     print("#{} {}".format(test_case, st))

T = int(input())
for tc in range(T):
    N = int(input())
    nums = list(map(int, input().split()))

    # 1. 어느 위치에 넣을 수를 찾을것인가?
    # 2. 해당 위치에 들어갈 수 찾기
    for index in range(N):
        # 0~N-1 위치
        # 원하는 수 <- 2가지 종류, 큰 or 작은 <- 번갈아가며
        found = 0 # 찾은 index
        if index % 2 == 0: # 큰 수 찾을 차례
            max_value = 0
            for i in range(index, N):
                if max_value < nums[i]:
                    max_value = nums[i]
                    found = i
        else : # 작은 수 찾을 차례
            min_value = 101
            for i in range(index, N):
                if min_value > nums[i]:
                    min_value = nums[i]
                    found = i
        nums[index], nums[found] = nums[found], nums[index]
    result = []
    for x in range(10):
        result.append(str(nums[x]))
        
    st = ' '.join(result)
    print("#{} {}".format(tc+1, st))
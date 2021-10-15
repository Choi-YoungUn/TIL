"""
sum_add_sort: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('sum_add_sort_input.txt')



def cut(lists):
    if len(lists) <= 1:
        return lists
    middle = len(lists)//2

    return merge(cut(lists[:middle]), cut(lists[middle:]))


def merge(list1, list2):
    global result
    li_1 = 0
    li_2 = 0
    temp = []
    if list1[-1] > list2[-1]:
        result += 1
    while li_1 < len(list1) and li_2 < len(list2):
        if list1[li_1] >= list2[li_2]:
            temp.append(list2[li_2])
            li_2 +=1
        elif list1[li_1] < list2[li_2]:
            temp.append(list1[li_1])
            li_1 +=1
        
    if li_1 < len(list1):
        temp += list1[li_1:]
    elif li_2 < len(list2):
        temp += list2[li_2:]
    return temp


T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input().strip())
    in_data = list(map(int,input().strip().split()))
    result = 0
    tmp = cut(in_data)
    print(f'#{tc} {tmp[len(tmp)//2]} {result}')


# ############### 병합 정렬
# def merge_sort(A):
#     if len(A) < 2: # 1개거나 0개
#         return A
#     mid = len(A)//2
#     low = merge_sort(A[:mid]) # 왼쪽 부분
#     high = merge_sort(A[mid:]) # 오른쪽 부분

#     if low[len(low) - 1] > high[len(high) - 1]:
#         global ans
#         ans += 1

#     temp = [-1] * len(A)
#     l = h = idx = 0
#     # l : low의 index
#     # h : high의 index
#     # idx : temp의 index
#     while l < len(low) and h < len(high):
#         if low[l] < high[h]:
#             temp[idx] = low[l]
#             l += 1
#         else :
#             temp[idx] = high[h]
#             h += 1
#         idx += 1
#     # low와 high를 서로 비교해서 진행, 두 리스트 중 하나라도 다 사용할 때까지

#     # 나머지 하나의 리스트를 전부 사용
#     while l < len(low): # low쪽이 남았다면
#         temp[idx] = low[l] # low에 남은 data를 temp에 추가
#         l += 1
#         idx += 1
#     while h < len(high) : # high쪽이 남았다면
#         temp[idx] = high[h]
#         h += 1
#         idx += 1

#     return temp


# def merge_sort_append(A):
#     if len(A) < 2: # 1개거나 0개
#         return A
#     mid = len(A)//2
#     low = merge_sort(A[:mid]) # 왼쪽 부분
#     high = merge_sort(A[mid:]) # 오른쪽 부분

#     if low[len(low) - 1] > high[len(high) - 1]:
#         global ans
#         ans += 1

#     temp = []
#     l = h = 0
#     # l : low의 index
#     # h : high의 index
#     # idx : temp의 index
#     while l < len(low) and h < len(high):
#         if low[l] < high[h]:
#             temp.append(low[l])
#             l += 1
#         else :
#             temp.append(high[h])
#             h += 1
#     # low와 high를 서로 비교해서 진행, 두 리스트 중 하나라도 다 사용할 때까지

#     # 나머지 하나의 리스트를 전부 사용
#     while l < len(low): # low쪽이 남았다면
#         temp.append(low[l])
#         l += 1
#     while h < len(high) : # high쪽이 남았다면
#         temp.append(high[h])
#         h += 1

#     return temp


# t = int(input())

# for tc in range(t):
#     n = int(input())
#     arr = list(map(int, input().split()))
#     ans = 0
#     sorted_arr = merge_sort_append(arr)
#     de = 1
#     print(f"#{tc + 1} {sorted_arr[n//2]} {ans}")
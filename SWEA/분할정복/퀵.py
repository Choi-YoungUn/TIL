"""
퀵: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('퀵_input.txt')


def q_sort(lists):
    if len(lists) <= 1:
        return lists

    check = 0
    li_down = []
    li_equl = []
    li_up = []
    middel = lists[len(lists) // 2]
    for check in lists:
        if check < middel:
            li_down.append(check)
        elif check > middel:
            li_up.append(check)
        else:
            li_equl.append(check)

    return q_sort(li_down) + li_equl+  q_sort(li_up)
    
def quick_sort(A, l, r):
    # A의 l~r범위를 정렬
    if l >= r:
        return
    p = partition(A, l, r)
    # p : pivot의 위치
    quick_sort(A, l, p - 1)
    quick_sort(A, p + 1, r)

def partition(A, l, r):
    # A의 l~r범위를 pivot을 기준으로 분류, pivot의 위치를 반환
    pivot = in_data[r]
    p = r
    # 실제로 분류할 범위 : l ~ r-1
    r -= 1

    while l <= r:
        while in_data[l] < pivot:
            # 정상인 경우
            l += 1 # 그냥 넘어감
        while in_data[r] > pivot:
            r -= 1 # 그냥 넘어감
        # 비정상적인 위치에 해당하는 l, r
        if l <= r : # l과 r의 위치가 정상적이라면
            in_data[l], in_data[r] = in_data[r], in_data[l]
            l += 1
            r -= 1
    in_data[l], in_data[p] = in_data[p], in_data[l]
    return l

T = int(input().strip())
for tc in range(1, T + 1):
    N = int(input().strip())
    in_data = list(map(int,input().strip().split()))
    quick_sort(in_data, 0, N - 1)
    print(f'#{tc} {in_data[len(in_data)//2]}')
    # print(f'#{tc} {result[len(result)//2]}')
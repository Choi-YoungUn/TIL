"""
max_miney: 
"""

import sys
sys.stdin = open('max_miney_input.txt')


#경우의 수 찾기, 매개변수로 몇번 바꿧는지 적는다.
def dfs(index):
    global result
    #횟수를 다 사용했다면
    if index == 0:
        #숫자로 바꿔보고
        temp = int(''.join(N_list))
        #가지고 있는 최대수보다 크다면 갱신
        if result < temp:
            result = temp
        return
    # 바꿔야 하니까 이중 포문
    for i in range(len(N_list)):
        #경우의 수를 찾는거니까 i보다 큰위치부터
        for j in range(i+1, len(N_list)):
            #두개의 위치를 바꾸고 나서
            N_list[i], N_list[j] = N_list[j], N_list[i]
            #가지치기 해야하니까 일단 합쳐보고
            temp = ''.join(N_list)
            #어떤수가 몇회차에 나왔는지 체크 1이면 안나온거니까 경우의수에 넣어주기
            if visited.get((temp, index-1), 1):
                #이숫자는 몇회차에 사용했으니까 체크해주고
                visited[(temp, index-1)] = 0
                #dfs도 돌려주고
                dfs(index-1)
            #다 썻으면 원상복귀
            N_list[i], N_list[j] = N_list[j], N_list[i]



T = int(input().strip())

for tc in range(1, T + 1):
    result = -1
    N, change = input().split()
    #바꾸기 편하려고 리스트화시킴
    N_list = list(N)
    change = int(change)

    #가지치기용 딕셔너리
    visited = {}
    
    dfs(change)
    print('#{} {}'.format(tc, result))

# ##############################
# # 시간 효율 업
# # memoization, dp
# # 가지치기 backtracking

# def dfs(now, cnt = 0):
#     # now번까지오는데, cnt번 교환을 했다.
#     global ans

#     if (k - cnt) % 2 == 0:
#         # 짝수번 남아서 현재 모양을 확정 가능
#         num = int("".join(map(str, num_list)))
#         ans = max(ans, num)

#     if cnt == k:
#         # 정확히 K번 사용이 끝!(한가지 방법을 완벽하게 만들었다!)
#         num = int("".join(map(str, num_list))) # 정수 리스트 -> 문자 리스트 -> 하나의 문자열 -> 하나의 정수
#         ans = max(ans, num)
#         return

#     if now >= len(num_list):
#         return
#     # 1. now번째 교환 X
#     dfs(now + 1, cnt)

#     # 2. now번째 교환 O
#     for i in range(now + 1, len(num_list)):
#         # i : now번째랑 교환해줄 위치0
#         num_list[now], num_list[i] = num_list[i], num_list[now]
#         num = int("".join(map(str, num_list)))
#         if not num in num_set[cnt + 1] :
#              # 이미 cnt + 1번 교환으로 num을 만든 적이 있다.
#             num_set[cnt + 1].add(num) # cnt + 1번 교환으로 지금 모양을 만들었다라고 추가
#             dfs(now + 1, cnt + 1)
#         #복구
#         num_list[now], num_list[i] = num_list[i], num_list[now]


# t = int(input())
# for tc in range(t):
#     num, k = input().split()
#     k = int(k)
#     num_list = list(map(int, str(num)))
#     #"123" -> [1, 2, 3]
#     num_set = [set() for _ in range(k + 1) ]
#     # num_set[] - index : 교환 횟수, value : index횟수를 소모하여 만든 모양
#     ans = -1
#     dfs(0)
#     print(f"#{tc + 1} {ans}")
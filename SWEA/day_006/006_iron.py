"""
006_iron: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('006_iron_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    N = list(input())
    iron = 0
    total_iron = 0
    x = 0
    while x < len(N):
        if N[x] == "(":
            x += 1
            if N[x] == ")":
                x += 1
                total_iron += iron
            else:
                iron += 1
        elif N[x] == ")":
            x += 1
            total_iron += 1
            iron -= 1
    print("#{} {}".format(test_case , total_iron))

#     T = int(input())
# for tc in range(T):
#     str1 = input()
#     stack = []
#     ans = 0
#     for i in range(len(str1)):
#         now = str1[i]
#         if now == "(":
#             stack.append(i)
#         else :#닫는 괄호
#             pop = stack[-1]
#             # 마지막으로 넣었던 값 확인
#             stack.pop(-1)
#             # 마지막으로 넣었던 값 삭제
#             if pop == i - 1: # 여는괄호가 바로 앞에 있었다.
#                 # 레이저를 쏘는 지점
#                 ans += len(stack)
#             else :
#                 # 레이저가 아니면 쇠막대기가 끝나는 지점
#                 ans += 1
#     print("#{} {}".format(tc + 1, ans))


# # 팁 : 일반적으로 괄호 문제 대부분이 stack으로 해결
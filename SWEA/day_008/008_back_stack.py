"""
008_back_stack: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('008_back_stack_input.txt')

T = int(input())
for tc in range(T):
    infix = input().rstrip()
    """
    string.strip() <- string에서 모든 공백 제거
    string.lstrip() <- string에서 왼쪽에 있는 공백들 제거
    string.rstrip() <- string에서 오른쪽에 있는 공백들 제거
    """
    print("#{} ".format(tc + 1), end = "")
    stack = []
    for ch in infix:
        if '0' <= ch <= '9':
            print(ch, end = "")
        elif ch == '(':
            stack.append(ch)
        elif ch == ')':
            while len(stack) != 0 and stack[-1] != '(':
                print(stack.pop(-1), end = "")
            stack.pop(-1)
        elif ch == '*' or ch == '/':
            while len(stack) != 0 and stack[-1] != "(" and \
                (stack[-1] == "*" or stack[-1]== "/") :
                print(stack.pop(-1), end = "")
            stack.append(ch)
        elif ch == '+' or ch == '-':
            while len(stack) != 0 and stack[-1] != '(':
                print(stack.pop(-1), end = "")
            stack.append(ch)

    while len(stack) != 0:
        print(stack.pop(-1), end = "")
    print("")

# T = int(input())
# for tc in range(T):
#     infix = input()
#     print("#{}".format(tc + 1), end = " ")

#     isp = [0] * 256 # isp[index] -> index : 문자(토큰), value : 우선순위
#     icp = [0] * 256 # icp[index] -> index : 문자(토큰), value : 우선순위

#     isp[ord("*")] = isp[ord("/")] = icp[ord("*")] = icp[ord("/")] = 2
#     isp[ord("+")] = isp[ord("-")] = icp[ord("+")] = icp[ord("-")] = 1
#     isp[ord("(")] = 0
#     icp[ord("(")] = 3

#     stack = []
#     for ch in infix:
#         if '0' <= ch <= '9':
#             print(ch, end = "")
#         elif ch == ")":
#             while stack[-1] != "(":
#                 print(stack.pop(-1), end = "")
#             stack.pop(-1)
#         else:
#             # 이번 문자가 stack에 있는 토큰보다 우선순위가 낮은 경우 계속 꺼내 출력
#             while len(stack) != 0 and icp[ord(ch)] <= isp[ord(stack[-1])]:
#                 print(stack.pop(-1), end = "")
#             # 이번 문자가 stack에 있는 토큰보다 우선순위가 높은 경우
#             stack.append(ch)

#     while len(stack) != 0:
#         print(stack.pop(-1), end = "")
#     print("")
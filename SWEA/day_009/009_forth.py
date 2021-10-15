"""
009_forth: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('009_forth_input.txt')


# T = int(input())
# for tc in range(1, T + 1):
#     result = list(map(str,input().split()))
#     stack = []
#     for x in range(len(result)):
#         try:
#             if result[x] == '+':
#                 temp = stack.pop(-1)
#                 temp = temp + stack.pop(-1)
#                 stack.append(temp)
#             elif result[x] == '-':
#                 temp = stack.pop(-1)
#                 temp = temp - stack.pop(-1)
#                 stack.append(temp)
#             elif result[x] == '*':
#                 temp = stack.pop(-1)
#                 temp = temp * stack.pop(-1)
#                 stack.append(temp)
#             elif  result[x] == '/':
#                 temp = stack.pop(-1)
#                 temp = temp / stack.pop(-1)
#                 stack.append(temp)
#             elif result[x] == '.':
#                 output = stack.pop(-1)

#                 if len(stack) != 0:
#                     raise
#             else:
#                 stack.append(int(result[x]))
#         except:
#             output = 'error'
#             break
#     if len(stack) != 0:
#         output = 'error'
#     print("#{} {}".format(tc, output))

T = int(input())
for tc in range(T):
    li = input().split()
    stack = []
    ans = ""
    for ch in li:
        # 연산자
        # 남는 얘들 : 숫자
        if ch == "+":
            if len(stack) < 2:
                ans = "error"
                break
            a = stack.pop(-1)
            b = stack.pop(-1)
            stack.append(a + b)
        elif ch == "*":
            if len(stack) < 2:
                ans = "error"
                break
            a = stack.pop(-1)
            b = stack.pop(-1)
            stack.append(a * b)
        elif ch == "-":
            if len(stack) < 2:
                ans = "error"
                break
            a = stack.pop(-1)
            b = stack.pop(-1)
            stack.append(b - a)
        elif ch == "/":
            if len(stack) < 2:
                ans = "error"
                break
            a = stack.pop(-1)
            b = stack.pop(-1)
            stack.append(b // a)
        elif ch == ".":
            ans = stack.pop(-1)
            break
        else :
            stack.append(int(ch))

    if len(stack) != 0:
        ans = "error"
    print("#{} {}".format(tc + 1, ans))
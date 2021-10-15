"""
009_submuchin2: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('009_submuchin2_input.txt')

for tc in range(1, 11):
    N = int(input())
    st = input().strip()
    result = ''
    stack = []
    for ch in st:
        if '0' <= ch <= '9':
            result += ch
            # print(ch, end = "")
        elif ch == '(':
            stack.append(ch)
        elif ch == ')':
            while len(stack) != 0 and stack[-1] != '(':
                result += stack.pop(-1)
                # print(stack.pop(-1), end = "")
            stack.pop(-1)
        elif ch == '*' :
            while len(stack) != 0 and stack[-1] != "(" and \
                (stack[-1] == "*" or stack[-1]== "/") :
                result += stack.pop(-1)
                # print(stack.pop(-1), end = "")
            stack.append(ch)
        elif ch == '+' :
            while len(stack) != 0 and stack[-1] != '(':
                result += stack.pop(-1)
                # print(stack.pop(-1), end = "")
            stack.append(ch)
    stack.clear()
    for ch in result:
        if ch == "+":
            if len(stack) < 2:
                break
            a = stack.pop(-1)
            b = stack.pop(-1)
            stack.append(a + b)
        elif ch == "*":
            if len(stack) < 2:
                break
            a = stack.pop(-1)
            b = stack.pop(-1)
            stack.append(a * b)
        else :
            stack.append(int(ch))
    print("#{} {}".format(tc, stack[0]))
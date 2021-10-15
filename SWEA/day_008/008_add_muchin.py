"""
008_add_muchin: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('008_add_muchin_input.txt')

for tc in range(1, 11):
    lens = int(input())
    string = input().strip()
    stack = []
    result = ''
    for x in range(lens):
        if '0' <= string[x] <= '9':
            result +=  string[x]
        elif string[x] == '+':
            while len(stack) > 0:
                result += stack.pop(-1)
            stack.append(string[x])
        elif string[x] == '*':
            stack.append(string[x])
            
    while len(stack) > 0:
        result += stack.pop(-1)

    for x in range(len(result)):
        if '0' <= result[x] <= '9':
            stack.append(int(result[x]))
        elif len(stack) > 0 and result[x] == '+':
            temp = stack.pop(-1)
            temp = temp + stack.pop(-1)
            stack.append(temp)
        elif len(stack) > 0 and result[x] == '*':
            temp = stack.pop(-1)
            temp = temp * stack.pop(-1)
            stack.append(temp)
    print("#{} {}".format(tc, stack[0]))

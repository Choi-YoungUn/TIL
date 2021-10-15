"""
007_password: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('007_password_input.txt')

T = 10
for test_case in range(1, T + 1):
    string = list(map(str, input().split()))
    stack = [0]
    sp = 0
    for x in range(int(string[0])):
        if sp == 0:
            sp += 1
            stack.append(string[1][x])
        elif stack[sp] == string[1][x]:
            stack.pop(-1)
            sp -= 1
        else:
            sp += 1
            stack.append(string[1][x])
    result = ''.join(stack[1:])
    print("#{} {}".format(test_case, result))
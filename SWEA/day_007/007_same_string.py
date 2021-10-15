"""
007_same_string: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('007_same_string_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    string = input().strip()
    stack = [0]
    sp = 0
    for x in range(len(string)):
        if sp == 0:
            sp += 1
            stack.append(string[x])
        elif stack[sp] == string[x]:
            stack.pop(-1)
            sp -= 1
        else:
            sp += 1
            stack.append(string[x])

    print("#{} {}".format(test_case, len(stack)-1))
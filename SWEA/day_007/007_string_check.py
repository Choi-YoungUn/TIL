"""
007_papertouch: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('007_string_check_input.txt')

def check(strings):
    stack = [0] * len(strings)
    sp = 0
    for x in range(len(strings)):
        de = strings[x]
        st = stack[sp]
        if strings[x] == '(' or strings[x] == '{':
            sp += 1
            stack[sp] = strings[x]
        elif strings[x] == ')' and stack[sp] == '(':
            stack[sp] = 0
            sp -= 1
        elif strings[x] == '}' and stack[sp] == '{':
            stack[sp] = 0
            sp -= 1
        elif strings[x] == ')':
            if stack[sp] == '{' or stack[sp] == 0:
                return 0
        elif strings[x] == '}':
            if stack[sp] == '(' or stack[sp] == 0:
                return 0
    if sp == 0:
        return 1
    else:
        return 0

T = int(input())
for test_case in range(1, T + 1):
    string = input().strip()
    print("#{} {}".format(test_case, check(string)))
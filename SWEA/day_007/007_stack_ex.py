"""
stack_ex: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('007_stack_ex.txt')

T = int(input())
for test_case in range(1, T + 1):
    stack = [-1] * 100
    sp = 0
    num = int(input())
    comend = []
    for x in range(num):
        comend.append(list(map(str, input().split())))

    print("#{}".format(test_case))
    for x in range(num):
        if comend[x][0] == 'i':
            sp += 1
            stack[sp] = comend[x][1]
        elif comend[x][0] == 'o':
            if stack[sp] == -1:
                print('empty')
            else:
                print(stack[sp])
                stack[sp] = -1
            if sp > 0:
                sp -= 1
        elif comend[x][0] == 'c':
            print(sp)
"""
iron: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('iron_input.txt')

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
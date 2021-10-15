"""
005_mirror: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('005_mirror_input.txt')

T =int(input())
for test_case in range(1, T + 1):
    string = input()
    temp = ""
    dics = {"b" : "d", "d" : "b", "p" : "q", "q" : "p"}
    for x in range(len(string) -1, -1, -1):
        temp += str(dics.get(string[x]))

    print("#{} {}".format(test_case , temp))

    
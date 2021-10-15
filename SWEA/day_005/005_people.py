"""
005_people: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('005_people_input.txt')

T =int(input())
for test_case in range(1, T + 1):
    string = input()
    temp = ["a", 'e', 'i', 'o', 'u']
    result = string[:]
    for char in temp:
        result = result.replace(char, '')
    print("#{} {}".format(test_case , result))
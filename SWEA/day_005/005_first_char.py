"""
005_first_char: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('005_first_char_input.txt')

T =int(input())
for test_case in range(1, T + 1):
    num = int(input())
    string = list(map(str,input().split()))
    result = ''
    for x in range(len(string)):
        result += chr(ord(string[x][0]) -32)
    print("#{} {}".format(test_case , result))
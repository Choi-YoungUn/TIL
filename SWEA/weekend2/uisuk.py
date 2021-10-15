"""
uisuk: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('uisuk_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    box = []
    result = ""
    size = 0
    for a in range(5):
        box.append(list(input()))
        if size < len(box[-1]):
            size = len(box[-1])
    
    for y in range(size):
        for x in range(5):
            if len(box[x]) > y:
                result += box[x][y]
    print("#{} {}".format(test_case , result))

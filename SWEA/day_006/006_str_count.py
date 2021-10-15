"""
006_str_count: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('006_str_count_input.txt')

T = int(input())
for test_case in range(1, T +1):
    temp_dic = {}
    temp = {0}
    string = input()
    str2 = input()
    for x in range(len(string)):
        temp.add(string[x])
    temp.remove(0)

    for x in range(len(str2)):
        temp_dic[str2[x]] = temp_dic.get(str2[x], 0) + 1
    result = 0
    for x in temp:
        if result < temp_dic.get(x):
            result = temp_dic.get(x)
    print("#{} {}".format(test_case , result))
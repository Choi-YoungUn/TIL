"""
005_GNS: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('005_GNS_input.txt')

T =int(input())
for test_case in range(1, T + 1):
    case_lens = list(map(str, input().split()))
    nums = list(map(str, input().split()))
    set_num = ["ZRO", "ONE", "TWO", "THR", "FOR", "FIV", "SIX", "SVN", "EGT", "NIN"]
    counts = [0] * 10
    temp = []
    result = ''
    for x in range(int(case_lens[1])):
        for index in range(len(set_num)):
            if set_num[index] == nums[x]:
                temp.append(index)
                counts[index] += 1
    for x in range(len(counts)):
        for y in range(counts[x]):
            result += set_num[x] + ' '

    result.strip()


    print("#{}".format(test_case))
    print(result)
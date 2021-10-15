"""
scan: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('scan_input.txt')

code_nums = {
    '0001101' : 0,
    '0011001' : 1,
    '0010011' : 2,
    '0111101' : 3,
    '0100011' : 4,
    '0110001' : 5,
    '0101111' : 6,
    '0111011' : 7,
    '0110111' : 8,
    '0001011' : 9   
}

def check_code(data, size):
    data = data[::size]
    ret = []
    for pos in range(0, len(data), 7):
        temp = data[pos:pos + 7]
        if temp not in code_nums:
            return 0
        else:
            ret.append(int(code_nums[temp]))
    return tuple(ret)

T = int(input())
for tc in range(1, T + 1):
    N, M = map(int, input().split())
    lines = set()
 
    for _ in range(N):
        temp = input().rstrip('0')
        if temp == "":
            continue
        lines.add(bin(int(temp, 16))[2:].rstrip('0'))
 
    codes = set()
    for line in lines:
        size = 1
        while line:
            line = line.zfill(size * 56)
            last = len(line)
            guess = line[last - size * 56:]
            able = check_code(guess, size)
            if able == 0:
                size += 1
            else:
                codes.add(able)
                line = line[:-size * 56].rstrip('0')
                size = 1
 
    answer = 0
    for code in codes:
        result = 0
        temp_ans = 0
        for i in range(len(code)):
            if i % 2 == 0:
                result += int(code[i]) * 3
            else:
                result += int(code[i])
            temp_ans += int(code[i])
 
        if result % 10 == 0:
            answer += temp_ans
 
    print("#{} {}".format(tc, answer))
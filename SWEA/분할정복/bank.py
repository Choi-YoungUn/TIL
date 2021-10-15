"""
bank: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('bank_input.txt')

T = int(input().strip())
for tc in range(1, T + 1):
    bin_num = int(input().strip(), 2)
    thi_num = list( input().strip())
    bins = bin(bin_num)[2:]
    bin_guess =[]
    thi_guess = []
    for x in range(0, len(bins) -1):
        bin_guess.append(bin_num ^ (1<<x))
    
    # print(thi_num)
    for x in range(len(thi_num)):
        for num in range(3):
            temp = thi_num[:]
            if str(num) != temp[x]:
                temp[x] = str(num)
                tmp = int(''.join(temp), 3)
                thi_guess.append(tmp)
    # print(bin_guess)
    # print(thi_guess)
    for result in bin_guess:
        if result in thi_guess:
            print(f'#{tc} {result}')
            break
    
    # print()

# 1010
# 212
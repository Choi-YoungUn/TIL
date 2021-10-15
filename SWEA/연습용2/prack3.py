"""
prack3: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('prack3_input.txt')

input()

code = {
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

T = int(sys.stdin.readline())
for tc in range(1, T + 1):
    N, M = map(int, sys.stdin.readline().split())
    bar_code = [sys.stdin.readline().strip() for _ in range(N)]
    temp = []
    for i in range(N):
        if int(bar_code[i]) != 0:
            j = M 
            while j >= 0:
                
                if bar_code[i][j-1] == '1':
                    temp.append(bar_code[i][j-7 : j])
                    j -= 6
                j -= 1
            if len(temp):
                break
    temp_num = []
    check_num = 0

    for x in range(len(temp)-1, -1, -1):
        temp_num.append(code[temp[x]])
        if x % 2:
            # print(f'add {code[temp[x]]}')
            check_num += code[temp[x]] * 3 
        else:
            # print(f'ord {code[temp[x]]}')
            check_num += code[temp[x]]
    if check_num % 10  :
        print(f'#{tc} {0}')
    else:
        print(f'#{tc} {sum(temp_num)}')
    


    # 0000 0111011 0110001 0111011 0110001 0110001 0001101 0010011 0111011 0000000000
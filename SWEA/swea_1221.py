"""
swea_1215: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('swea_1221_input.txt')


str_to_num = ["ZRO", "ONE", "TWO", "THR", "FOR",
 "FIV", "SIX", "SVN", "EGT", "NIN"]
c = input() 
for als in range(10):  #10번의 테스트 케이스
      
    d = input()         
    k = list(input().split())

    result = ''

    for lis in range(len(k)):
        k[lis] = str_to_num.index(k[lis])
    
    k.sort()

    for liss in range(len(k)):
        result += str_to_num[k[liss]] + ' '
    
    print("#{}".format(als + 1))
    print(result)


    




"""
swea_1215: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('swea_4466_input.txt')



T = int(input())
for als in range(T):  #10번의 테스트 케이스
      
    d = list(map(int,(input().split()))) 
    k = list(map(int,(input().split())))
    temp = 0
    k.sort(reverse= 1)
    for a in range(d[1]):
        temp += k[a]

    
    print("#{} {}".format(als + 1, temp))

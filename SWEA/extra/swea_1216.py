"""
swea_1215: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('swea_1216_input.txt')

def check(num, lists):
    pass

for als in range(10):  #10번의 테스트 케이스
    c = []              #글자판 저장 리스트
    k = int(input())     # 회문길이
    for a in range(100):
        c.append((input()))
        
    print("#{} {}".format(als + 1,check(c))) #함수 호출과 출력
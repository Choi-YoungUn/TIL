"""
swea_1215: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('swea_1215_input.txt')

def check(num, lists):
    count = 0
    if not(num % 2):  #길이가 짝수일때
            
            #가로줄 검사
        for y in range(8):  #세로축
            for x in range(8 - num +1):   #가로축
                for rang in range(num // 2):
                    if lists[y][x + rang] == lists[y][x + num - 1 - rang]:#각 대응 자리 비교
                        pass 
                    else:
                        break #틀리다면 끝낸다
                else:
                    count += 1
        for y in range(8 - num +1):  #세로축
            for x in range(8):   #가로축
                for rang in range(num // 2):
                    if lists[y + rang][x] == lists[y+ num - 1 - rang][x ]:#각 대응 자리 비교
                        pass
                    else:
                        break   #틀리다면 끝낸다
                else:
                    count += 1
        return count        
    else:  #길이가 홀수일때
              #세로줄 검사
        for y in range(8):  #세로축
            for x in range(8 - num +1):   #가로축
                for rang in range(num // 2):
                    if lists[y][x + rang] == lists[y][x + num - 1 - rang]:#각 대응 자리 비교   
                        pass
                    else:
                        break    #틀리다면 끝낸다
                else:
                    count += 1
        for y in range(8 - num +1):  #세로축
            for x in range(8):   #가로축
                for rang in range(num // 2):
                    if lists[y + rang][x] == lists[y+ num - 1 - rang][x ]:#각 대응 자리 비교
                        pass
                    else:
                        break    #틀리다면 끝낸다
                else:
                    count += 1
        return count

for als in range(10):  #10번의 테스트 케이스
    c = []              #글자판 저장 리스트
    k = int(input())     # 회문길이
    for a in range(8):
        c.append((input()))
        
    print("#{} {}".format(als + 1,check(k, c))) #함수 호출과 출력
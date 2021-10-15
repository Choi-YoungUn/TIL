"""
swea_1215: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('swea_1961_input.txt')

import copy   #변수간에 데이터를 같이 가르켜서 변형되는 것을 방지

T = int(input())  #테스트 입력

for als in range(T):  #10번의 테스트 케이스
    temp_90 = []          #90도 튼 리스트
    temp_180 = []         #180도
    temp_270 = []          #270도
    list_first = []        #입력받을 리스트
    num = int(input())     #한 변의 길이
    for a in range(num):
        list_first.append(list(map(int,(input().split()))))  #입력받는다.
    temp = []               #중간저장할 리스트
    for k in range(num):
        temp.append([0] * num)  #입력받은 리스트와 같은 크기로 만들어준다.
    
    print("#{}".format(als + 1))  #출력 상단 테스트 번호

    for z in range(3):          #90도씩 3번 돌아주자
        for y in range(num):       #가로 세로 축을 모두 돌자
            for x in range(num):
                temp[y][x] = list_first[num- x - 1][y] # 자리를 돌려주는 시퀀스.
                        
        list_first = copy.deepcopy(temp)   #90도 회전한 것을 복사하여 저장
        if z == 0:
            temp_90 = copy.deepcopy(temp)   #90도 회전한 것을 복사저장
        elif z == 1:
            temp_180 = copy.deepcopy(temp) #90도 x 2 회전한 것을 복사저장
        elif z == 2:
            temp_270 = copy.deepcopy(temp) #90도 x 3 회전한 것을 복사저장
    
    rel = [temp_90, temp_180, temp_270] #세개를 한번에 컨트롤 하도록 묶기

    
    for c in range(num):   #출력합시다.  세로줄 출력
        for b in range(3):   #회전한 3개의 리스트 순서대로 출력
            for d in range(num):    #리스트 내의 가로줄 출력
                print(rel[b][c][d], end = '') #줄 안바뀌게 
            print(' ', end = '')   #하나의 리스트 끝나면 띄어주기
        print('')    #한 줄 출력후 줄바꿈!


    
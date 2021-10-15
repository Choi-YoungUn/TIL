

import sys
sys.stdin = open('sw_day1_view_input.txt')



for als in range(10):  #10번의 테스트 케이스
    longs = int(input())          #가로길이    
    k = list(map(int,input().split())) 
       
    counts = 0
    for x in range(2, len(k) - 2):
        temp = [k[x - 2], k[x - 1], k[x + 1], k[x + 2]]
        for st in range(3):
            for stt in range(st, 3):
                if temp[st] > temp[st+1]:
                    temp[st], temp[st+1] = temp[st+1], temp[st]
        if k[x] > temp[-1]:
            counts += k[x] - temp[-1] 


    print("#{} {}".format(als + 1, counts))

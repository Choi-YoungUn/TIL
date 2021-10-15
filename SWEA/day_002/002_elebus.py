"""
002_elebus: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('002_elebus_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    knm = list(map(int,input().split()))
    stops = list(map(int,input().split()))
    
    tatal_stops = [0] * (knm[1]+1)
    
    for gus in range(len(stops)):
        tatal_stops[stops[gus]] = 1

    now = 0
    bus_stop_check = 0
    break_po = 0
    while True:
        if now + knm[0] >= knm[1]:
            break
        else:
            for check_stop in range(knm[0], 0 , -1):
                if 1 not in tatal_stops[now + 1 : now + 1 +knm[0]]:
                    break_po = 1
                    bus_stop_check = 0
                    break

                if tatal_stops[now+check_stop] == 1:
                    now = now+check_stop
                    bus_stop_check += 1
                    break
        if break_po == 1:
            break
                
    print("#%d %d" %(test_case , bus_stop_check))
    

    

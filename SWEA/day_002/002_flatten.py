"""
002_flatten: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('002_flatten_input.txt')

T = 10
for test_case in range(1, T + 1):
    # num = int(input())
    # box = list(map(int,input().split()))
    # for x in range(num):
    #     maxx = 1
    #     max_in = 0
    #     minn = 100
    #     min_in =0
    #     for y in range(len(box)):
    #         if maxx < box[y]:
    #             maxx = box[y]
    #             max_in = y
    #         if minn > box[y]:
    #             minn = box[y]
    #             min_in = y
            
    #     box[max_in] -= 1
    #     box[min_in] += 1

    # maxy = 1
    # miny = 100
    # for z in range(len(box)):
    #     if maxy < box[z]:
    #         maxy = box[z]      
    #     if miny > box[z]:
    #         miny = box[z]

    # print("#%d %s" %(test_case , maxy - miny))

    #########################################
    # for x in range(num):
        
    #     maxx = max(box)
    #     minn = min(box)
    #     box[box.index(maxx)] -= 1
    #     box[box.index(minn)] += 1

    # print("#%d %s" %(test_case , max(box) - min(box)))
    ##############################################

    # count list
    #어떤 높이가 몇개 있는지 
    dumps = int(input())
    boxes = list(map(int, input().split()))

    # counts 리스트 만들기
    # 어떤 높이가 몇 개 있는지 세어둔 리스트
    counts = [0] * 101
    # index : 높이, value : 해당 높이가 몇 개 있는가?
    max_height = 0 # 최대 높이
    min_height = 101 # 최소 높이
    for box in boxes:
        counts[box] += 1
        if max_height < box :
            max_height = box
        if min_height > box :
            min_height = box

    for i in range(dumps):
        counts[max_height] -= 1
        counts[max_height - 1] += 1
        counts[min_height] -= 1
        counts[min_height + 1] += 1
        if counts[max_height] == 0:
            max_height -= 1
        if counts[min_height] == 0:
            min_height += 1

    ans = max_height - min_height
    print("#{} {}".format(test_case + 1, ans))
         
"""
myroom: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('myroom_input.txt')

T = int(input())
for test_case in range(1, T + 1):
    room = [0] * 201
    people = int(input())
    moves = []
    result = 0
    for x in range(people):
        moves.append(list(map(int,input().split())))

    for x in range(len(moves)):
        if moves[x][0] % 2 == 1:
            moves[x][0] += 1
        if moves[x][1] % 2 == 1:
            moves[x][1] += 1

        if moves[x][0] <= moves[x][1]:
            start = moves[x][0] // 2
            end = moves[x][1] //2
        else:
            start = moves[x][1] //2
            end = moves[x][0] //2
        
        for num in range(start, end + 1):
            room[num] += 1
            if result < room[num]:
                result = room[num]

    print("#{} {}".format(test_case , result))
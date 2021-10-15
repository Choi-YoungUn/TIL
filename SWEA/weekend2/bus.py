"""
bus: 문제명을 입력해주세요 :)
"""

# import sys
# sys.stdin = open('bus_input.txt')

T =int(input())
for test_case in range(1, T + 1):
    N = int(input())
    bus_stop = [0] * 5000
    bus_line = []
    print_line = []
    for X in range(N):
        bus_line.append(list(map(int,input().split())))

    P = int(input())
    for X in range(P):
        print_line.append(int(input()))

    for x in range(N):
        for y in range(bus_line[x][0] -1, bus_line[x][1]):
            bus_stop[y] += 1
    result =''
    for x in range(len(print_line)):
        result += str(bus_stop[print_line[x]-1]) + ' '
    result.strip()
    print("#{} {}".format(test_case , result))

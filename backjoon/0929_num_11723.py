import sys
M = int(sys.stdin.readline().rstrip())
# 0 은 없다  1 이 있다 표현
S = 0
for time in range(M):
    string = list(sys.stdin.readline().split())
    if len(string) == 1:
        if string[0] == 'all':
            S = (1 << 21) -1
        elif string[0] == 'empty':
            S = 0
    else:
        if string[0] == 'add':
            S = S | (1 << int(string[1]))
        elif string[0] == 'remove':
            S = S & ~(1 << int(string[1]))
        elif string[0] == 'check':
            if S & (1 << int(string[1])):
                print(1)
            else:
                print(0)
        elif string[0] == 'toggle':
            S = S^(1 << int(string[1]))
        
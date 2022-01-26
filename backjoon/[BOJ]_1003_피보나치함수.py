import sys

T = int(sys.stdin.readline().rstrip())
DP = [[0, 0] for _ in range(41)]
for tc in range(T):
    N = int(sys.stdin.readline().rstrip())
    ONE = 0
    ZERO = 0

    def fabo(NUM):
        global DP
        if DP[NUM] != [0, 0]:
            return DP[NUM]
        
        if NUM == 0:
            DP[0] = [1, 0]
            return DP[0]
        elif NUM == 1:
            DP[1] = [0, 1]
            return  DP[1]
        else:
            DP[NUM] = [fabo(NUM-1)[0] + fabo(NUM-2)[0], fabo(NUM-1)[1] + fabo(NUM-2)[1]]
            return DP[NUM]
    
    print(f"{fabo(N)[0]} {fabo(N)[1]}")
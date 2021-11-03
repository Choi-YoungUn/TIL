import sys

def coin(N):
    global result
    if N % 10 >0:
        return False
    if N >= 300:
        result[0] = N // 300
        N = N % 300

    if N >= 60:
        result[1] = N // 60
        N = N % 60

    if N >= 10:
        result[2] = N // 10
    result = ' ' .join(list(map(str, result)))
    return True

k = int(sys.stdin.readline())

result = [0]* 3
if coin(k):
    print(result)
else:
    print('-1')
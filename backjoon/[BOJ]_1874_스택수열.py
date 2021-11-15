import sys

N = int(sys.stdin.readline())
stack = []
result = []
num = 1
t = 1
for x in range(N):
    get = int(sys.stdin.readline())
    while get >= num:
        stack.append(num)
        num += 1
        result.append('+')
    

    if stack[-1] == get:
        stack.pop()
        result.append('-')
    else:
        t = 0
        break
if t == 0:
    print('NO')
else:
    for x in range(len(result)):
        print(result[x])
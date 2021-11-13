import sys

N = int(sys.stdin.readline())
STR = sys.stdin.readline().rstrip()
stack = []
cnt_list = [0] * N
result = 0

for st in range(len(STR)):
    if STR[st] == '(':
        stack.append([STR[st], st])
    elif STR[st] == ')':
        if len(stack) > 0:
            if stack[-1][0] == '(':
                cnt_list[stack[-1][1]] = 1
                cnt_list[st] = 1
                stack.pop()
cnt = 0
for x in cnt_list:
    if x == 1:
        cnt += 1
    else:
        cnt = 0
    if result < cnt:
        result = cnt
print(result)
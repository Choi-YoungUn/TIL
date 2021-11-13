import sys

result = 0
for _ in range(int(sys.stdin.readline())):
    string = sys.stdin.readline().rstrip()
    stack = []
    for x in string:
        if len(stack) == 0:
            stack.append(x)
        elif stack[-1] == x:
            stack.pop()
        else:
            stack.append(x)
    if len(stack) == 0:
        result += 1

print(result)

infix = input().rstrip()

stack = []
for ch in infix:
    if 'A' <= ch <= 'Z':
        print(ch, end = "")
    elif ch == '(':
        stack.append(ch)
    elif ch == ')':
        while len(stack) != 0 and stack[-1] != '(':
            print(stack.pop(-1), end = "")
        stack.pop(-1)
    elif ch == '*' or ch == '/':
        while len(stack) != 0 and stack[-1] != "(" and \
            (stack[-1] == "*" or stack[-1]== "/") :
            print(stack.pop(-1), end = "")
        stack.append(ch)
    elif ch == '+' or ch == '-':
        while len(stack) != 0 and stack[-1] != '(':
            print(stack.pop(-1), end = "")
        stack.append(ch)
while len(stack) != 0:
    print(stack.pop(-1), end = "")
print("")
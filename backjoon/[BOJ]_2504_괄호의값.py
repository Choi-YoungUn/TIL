import sys

def check(lists):
    string = lists
    stack = []
    
    for st in string:
        if st == ']':
            if len(stack) == 0:
                return 0
            tmp = 0
            while stack:
                now = stack.pop()
                if now == '(':
                    return 0
                elif now == '[':
                    if tmp == 0:
                        stack.append(3)
                    else:
                        stack.append(3 * tmp)
                    break
                else:
                    if tmp == 0:
                        tmp = int(now)
                    else:
                        tmp = tmp +  int(now)
        elif st == ')':
            if len(stack) == 0:
                return 0
            tmp = 0
            while stack:
                now = stack.pop()
                if now == '(':
                    if tmp == 0:
                        stack.append(2)
                    else:
                        stack.append(2 * tmp)
                    break
                elif now == '[':
                    return 0
                else:
                    if tmp == 0:
                        tmp = int(now)
                    else:
                        tmp = tmp +  int(now)
        else:
            stack.append(st)
    result = 0
    for x in stack:
        if x == "(" or x == "[":
            return 0
        else:
            result += x
    return result

str = sys.stdin.readline().rstrip()
print(check(str))
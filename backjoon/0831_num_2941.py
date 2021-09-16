string = input().strip()
result = []
index = len(string) -1
while index >= 0:
    if string[index] == '=':
        if string[index-1] == 'c':
            result.append(string[index - 1] + string[index])
            index -= 1
        elif string[index-1] == 'z':
            if index - 2 >= 0 and string[index - 2] == 'd':
                result.append(string[index - 2] + string[index - 1] + string[index])
                index -= 2
            else:
                result.append(string[index - 1] + string[index])
                index -= 1
        elif string[index-1] == 's':
            result.append(string[index - 1] + string[index])
            index -= 1
    elif string[index] == '-':
        result.append(string[index - 1] + string[index])
        index -= 1
    elif string[index] == 'j' and (string[index - 1] == 'l' or string[index - 1] == 'n'):
        result.append(string[index - 1] + string[index])
        index -= 1
    else:
        result.append(string[index])
    index -= 1
print(len(result))
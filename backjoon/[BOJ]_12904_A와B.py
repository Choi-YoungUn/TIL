import sys

st_str = sys.stdin.readline().rstrip()
end_str = sys.stdin.readline().rstrip()
result = 0

while len(end_str) >= len(st_str):
    if end_str == st_str:
        result = 1
        break
    else:
        if end_str[-1] == 'A':
            end_str = end_str[:-1]
        elif end_str[-1] == 'B':
            end_str = end_str[:-1]
            tmp = ''
            for x in range(len(end_str)-1 ,-1, -1):
                tmp += end_str[x]
            end_str = tmp
            
print(result)
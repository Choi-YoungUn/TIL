import sys


byte = sys.stdin.readline()

re_list = []
for index in range(len(byte)-1, -1, -7):
    temp = byte[index-7:index]
    result = 0
    for x in range(len(temp)):
        if temp[x] == '1':
            result += 2** (6-x)
    re_list.append(result)

    print(temp, result)
strs = ''
for x in range(len(re_list)-1, -1, -1):
    strs += str(re_list[x]) + ','

print(strs[2:-1])


#0000000111100000011000000111100110000110000111100111100111111001100111
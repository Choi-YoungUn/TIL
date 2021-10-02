def check(lists, num):
    temp = lists
    for x in range(len(temp)):
        if x == num -1:
            return 'YES'
        for y in range(x + 1, len(temp)):
            if temp[x] == temp[y][:len(temp[x])]:
                return 'NO'
    return 'YES'

T= int(input())
for test_case in range(1, T + 1):
    time = int(input())
    temp = []
    for x in range(time):
        temp.append(int(input()))
    temp.sort()
    temp = list(map(str,temp))
    nu = len(temp[-1])
    print(check(temp ,nu))
T = int(input())
for test_case in range(1, T + 1):
    temp = list(map(int, input().strip()))

    for i in range(len(temp) - 1, 0, -1):
        swapped = False
        for j in range(i):
            if temp[j] > temp[j + 1]:
                temp[j], temp[j + 1] = temp[j + 1], temp[j]
                swapped = True
        if not swapped:
            break

    if temp[0] == temp[1] == temp[2] or temp[0] + 2 == temp[1] + 1 == temp[2]:
        if temp[3] == temp[4] == temp[5] or temp[3] + 2 == temp[4] + 1 == temp[5]:
            print('#{} Baby Gin'.format(test_case))
        else:
            print('#{} Lose'.format(test_case))
    else:
        print('#{} Lose'.format(test_case))

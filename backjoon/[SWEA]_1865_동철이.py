def sel(num, select, pre):
    global res
    if res >= pre:
        return

    if len(select) == people:
        if res < pre:
            res = pre
        return

    for a in range(people):
        if tmp[a] == 0:
            tmp[a] = 1
            sel(num+1, select + [a], pre * (present[num][a] / 100))
            tmp[a] = 0
        
for tc in range(1, int(input())+1):
    people = int(input())
    present = [list(map(int, input().rstrip().split())) for _ in range(people)]
    res = 0
    for k in range(people):
        tmp = [0] * people
        tmp[k] = 1
        sel(1, [k], present[0][k] / 100)
    
    res = format(res * 100, ".6f")
    
    print(f'#{tc} {res}' )
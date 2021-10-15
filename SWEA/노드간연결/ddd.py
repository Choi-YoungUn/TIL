def co1(num, pa):
    if num == N:
        result = ' '.join(pa)
        print(result)
        return
    for x in range(1, 7):
        co1(num+1, pa + [str(x)])

def co2(num, pa, i):
    if num == N:
        result = ' '.join(pa)
        print(result)
        return
    for x in range(i, 7):
        co2(num+1, pa + [str(x)], x)


def co3(num, pa):
    if num == N:
        result = ' '.join(pa)
        print(result)
        return
    for x in range(1, 7):
        if visit[x] != 0:
            continue
        visit[x] = 1
        co3(num+1, pa + [str(x)])
        visit[x] = 0
    

visit = [0] * (7)
N, code = map(int, input().split())
if code == 1:
    co1(0, [])
elif code == 2:
    co2(0, [], 1)
elif code == 3:
    co3(0, [])

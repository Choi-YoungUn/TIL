import sys


def sc_day(now_day, now_cost):
    global result
    if now_day == N:
        if result < now_cost:
            result = now_cost
        return
    elif now_day == N-1:
        tmp = now_cost
        if days[now_day][0] == 1:
            tmp  += days[now_day][1]
        if result < tmp:
            result = tmp
        return
    
    if now_day + days[now_day][0] <= N:
        sc_day(now_day + days[now_day][0], now_cost + days[now_day][1])
    if now_day < N:
        sc_day(now_day + 1, now_cost)


N =int(sys.stdin.readline())
days = []
for _ in range(N):
    day, cost = map(int, sys.stdin.readline().split())
    days.append((day, cost))
result = 0
sc_day(0, 0)

print(result)
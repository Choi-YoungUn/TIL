house = int(input())
cost = []
for x in range(house):
    cost.append(list(map(int, input().split())))
for x in range(1, len(cost)):
    cost[x][0] = min(cost[x - 1][1], cost[x - 1][2]) + cost[x][0]
    cost[x][1] = min(cost[x - 1][0], cost[x - 1][2]) + cost[x][1]
    cost[x][2] = min(cost[x - 1][0], cost[x - 1][1]) + cost[x][2]

print(min(cost[-1]))
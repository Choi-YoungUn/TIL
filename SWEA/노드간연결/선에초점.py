# 선에 초점
"""
6 11
0 1 32
0 2 31
0 5 60
0 6 51
1 2 21
2 4 46
2 6 25
3 4 34
3 5 18
4 5 40
4 6 51
"""

def Find(x):
    if x == parents[x]:
        return x
    else:
        px = Find(parents[x])
        parents[x] = px
        return px

def Union(x, y):
    px = Find(x)
    py = Find(y)
    parents[py] = px


n, m = map(int, input().split())
parents = [i for i in range(n + 1)]
edges = []
for i in range(m):
    f, t, cost = map(int, input().split())
    edges.append( (cost, f, t) )
edges.sort()
total_cost = 0
for cost, f, t in edges:
    if Find(f) == Find(t):
        continue
    Union(f, t)
    total_cost += cost

print(total_cost)
# 유튜브 수업때 설명한 코드들은 '모든 node가 전부 연결 가능하다.'
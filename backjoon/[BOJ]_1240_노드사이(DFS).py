import sys

def dfs(now, far):
    global kill
    now_far = far
    if kill:
        return

    if now == end_node:
        print(now_far)
        kill = True
        return

    for next in tree[now]:
        if kill:
            return

        if visied[next[0]] == 0:
            visied[next[0]] = 1
            dfs(next[0], now_far + next[1])
            visied[next[0]] = 0


NM = list(map(int, sys.stdin.readline().split()))
tree = [[ ] for _ in range(NM[0])]
visied = [0] * NM[0]
for _ in range(NM[0] -1):
    node = list(map(int, sys.stdin.readline().split()))
    tree[node[0]-1].append([node[1]-1, node[2]])
    tree[node[1]-1].append([node[0]-1, node[2]])
end_node = -1
kill = False
for _ in range(NM[1]):
    visied = [0] * NM[0]
    kill = False
    goto = list(map(int, sys.stdin.readline().split()))
    end_node = goto[1] -1
    visied[goto[0]-1] = 1
    dfs(goto[0] -1, 0)
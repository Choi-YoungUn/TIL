import sys
sys.setrecursionlimit(100000)


def dfs(li_s, li_e):
    if li_s > li_e:
        return
    N = box[li_s]
    mid = li_e
    while N < box[mid]:
        mid -= 1
    dfs(li_s + 1, mid)
    dfs(mid + 1, li_e)
    print(box[li_s])


box = list(map(int, sys.stdin.read().split()))

dfs(0, len(box) - 1)
# 50, 30, 24, 5, 28, 45, 98, 52, 60
# 50 30 98 24 45 52 00 05 28 00 00 00 60 00 00
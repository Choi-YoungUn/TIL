# from to
# 3 1
# 3 5
# 1 2
# 1 4

graph1 = [
    #to:1  2  3  4  5
    [0, 0, 0, 0, 0, 0], #from
    [0, 0, 1, 0, 1, 0], # 1
    [0, 0, 0, 0, 0, 0], # 2
    [0, 1, 0, 0, 0, 1], # 3
    [0, 0, 0, 0, 0, 0], # 4
    [0, 0, 0, 0, 0, 0]  # 5
]
for i in range(4):
    frm, to = map(int, input().split())
    graph1[frm][to] = 1

graph2 = [
    [], # from
    [2, 4], # 1
    [], # 2
    [1, 5], # 3
    [], # 4
    []  # 5
]
for i in range(4):
    frm, to = map(int, input().split())
    graph2[frm].append(to)

# k진 트리
# from to
# 3 1 1(left)
# 3 5 2(right)
# 1 2 1
# 1 4 2
tree1 = [
#자식 l  r
    [0, 0], # from
    [2, 4], # 1
    [0, 0], # 2
    [1, 5], # 3
    [0, 0], # 4
    [0, 0]  # 5
]
for i in range(4):
    frm, to, pos = map(int, input().split())
    if pos == 1:
        tree1[frm][0] = to
    elif pos == 2:
        tree1[frm][1] = to

# 부모를 저장
#node번호 : 0, 1, 2, 3, 4, 5
tree2 = [  0, 3, 1,-1, 1, 3]
for i in range(4):
    frm, to = map(int, input().split())
    tree2[to] = frm

# k진트리 1차원
# node번호를 계산
#node번호 : 0, 1, 2, 3, 4, 5
#node 값  :-1, 3, 1, 5, 2, 4
tree3 = [  -1, 3, 1, 5, 2, 4]
# 1 3
# 2 1
# 3 5
# 4 2
# 5 4
for i in range(4):
    index, value = map(int, input().split())
    tree3[index] = value
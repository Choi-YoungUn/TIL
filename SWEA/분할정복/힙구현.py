# 힙 구현 코드

def enq(n):
    global last
    last += 1
    tree[last] = n
    c = last
    p = c//2
    while p>=1 and tree[p]<tree[c]:
        tree[p], tree[c] = tree[c], tree[p]
        c = p
        p = c//2


def deq():
    global last
    tmp = tree[1]
    tree[1] = tree[last]
    last -= 1
    p = 1
    c1 = 2*p
    c2 = 2*p + 1
    while c1<=last:     # 자식이 하나라도 있으면
        if c2<=last:     # 자식이 둘이면
            if tree[c1]>=tree[c2] and tree[c1]>tree[p]:
                tree[c1], tree[p] = tree[p], tree[c1]
                p = c1
            elif tree[c1]<tree[c2] and tree[c2]>tree[p]:
                tree[c2], tree[p] = tree[p], tree[c2]
                p = c2
            c1 = p*2
            c2 = p*2+1
        else:           # 왼쪽자식만 있는 경우
            if tree[c1]>tree[p]:
                tree[c1], tree[p] = tree[p], tree[c1]
            break
    return tmp

tree = [0]*101      # 최대 100번노드까지..  최대힙
last = 0            # 마지막 노드 번호
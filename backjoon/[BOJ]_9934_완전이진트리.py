def inorder(now, depth):
    global cnt
    global K
    if depth > K:
        return
    inorder(now * 2, depth + 1)
    G[now] = result[cnt] # 이번에 출력된 얘는 cnt번째 얘
    cnt += 1 # 다음은 지금 cnt바로 다음 번호
    inorder(now * 2 + 1, depth + 1)

K = int(input())
G = [0] * (1 << K)
result = list(map(int, input().split()))
# result : inorder의 결과
cnt = 0
inorder(1,1)
cnt = 1
for i in range(K):
    # i : 깊이
    for j in range(1 << i):
        print(G[cnt], end = " ")
        cnt += 1
    print("")
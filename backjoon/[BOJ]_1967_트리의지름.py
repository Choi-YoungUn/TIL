import sys
sys.setrecursionlimit(50000)

#제일 먼 위치를 찾기위한 여정.
def dfs_st(now, far):
    global start_vi
    #이전 노드 이외에 연결된 다른 노드가 있을시 false로 변경됨
    check = True

    for nows in node[now]:
        #지금 노드랑 연결된 다른 노드중 방문하지 않은 것이 있으면
        if visit[nows[0]] == 0:
            visit[nows[0]] = 1
            #이동!
            dfs_st(nows[0], far + nows[1])
            visit[nows[0]] = 0
            #일단 끝노드는 아니므로 false
            check = False
    #만약 끝 노드라면 시작점부터 지금까지의 거리를 저장해두자
    if check:
        start_vi[now] = far
        return

#결정된 시작노드 부터 막다른 노드까지 계산하자
def dfs(now, far):
    global result
    check = True

    for nows in node[now]:
        if visit[nows[0]] == 0:
            visit[nows[0]] = 1
            dfs(nows[0], far + nows[1])
            visit[nows[0]] = 0
            check = False
    #이게 끝 노드라면 지금까지 찾은 거리와 비교해서 넣어주자
    if check:
        if result < far:
            result = far
        return



N = int(sys.stdin.readline())
# N이 1일경우 바로 0이 출력되도록 해주자.
if N > 1:
    node = [[] for _ in range(N + 1)]
    for _ in range(N -1):
        no1, no2, far = map(int, sys.stdin.readline().split())
        node[no1].append([no2, far])
        node[no2].append([no1, far])

    visit = [0] * (N+1)
    start_vi = [0] * (N+1)
    result = 0
    # 한개의 다른 노드와 연결된 부분을 찾아서
    # 해당 노드로부터 모든 노드각각에 도달하는 거리를 찾는다
    for start in range(1, N+1):
        #지금 노드와 연결된 노드가 2개이상이면 찾지마.
        if len(node[start]) > 1:
            continue
        #한개랑만 연결되었다면 현재꺼 체크
        visit[start] = 1
        #갈 노드 방문표시
        visit[node[start][0][0]] = 1
        #DFS다이브!
        dfs_st(node[start][0][0], node[start][0][1])
        #하나만 찾으면 된다. 그러므로 끝!
        break

    #위에서 계산해서 저장한 거리중 제일 먼 노드를 찾는다
    start_idx = 0
    tmp = 0
    visit = [0] * (N+1)
    #제일 멀다고 체크된 노드는?
    for idx in range(1, N+1):
        if start_vi[idx] > tmp:
            tmp = start_vi[idx]
            start_idx = idx
    #제일 멀다고 체크된 노드에서 시작해주자 다시...
    #제일먼 노드가 시작점이 되어 다른 모든 노드와의 거리를 계산하자
    visit[start_idx] = 1
    for next in node[start_idx]:
        #연결된 다음 노드로~
        visit[next[0]] = 1
        dfs(next[0], next[1])
        visit[next[0]] = 0

    print(result)
else:
    print('0')
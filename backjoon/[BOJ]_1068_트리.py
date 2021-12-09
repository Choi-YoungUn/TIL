import sys
from collections import deque

N = int(sys.stdin.readline().rstrip())
tree = list(map(int, sys.stdin.readline().rstrip().split()))
D = int(sys.stdin.readline().rstrip())

# 제거 자리에 -2로 만들기
tree[D] = -2
q = deque()
q.append(D)
result = 0

# 제거된 노드를 부모로 두고있는 자식노드 찾아서 -2로 만들기
while q:
    idx = q.popleft()
    for x in range(N):
        if tree[x] == idx:
            q.append(x)
            tree[x] = -2

#모든 노드에 대하여 
for check_idx in range(N):
    #현재 노드를 부모노드로 가지고 있다면 취소
    if check_idx in tree:
        continue
    #제거된 노드라면 취소
    if tree[check_idx] == -2:
        continue
    #위에 두가지경우를 통과하면 갯수 추가
    result += 1
        
print(result)
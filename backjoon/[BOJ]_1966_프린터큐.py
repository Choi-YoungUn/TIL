import sys
from collections import deque

T =  int(sys.stdin.readline().rstrip())

for tc in range(1, T + 1):
    NM = list(map(int, sys.stdin.readline().rstrip().split()))
    in_que = list(map(int, sys.stdin.readline().rstrip().split()))
    q = deque()
    for a in in_que:
        q.append(a)
    
    cnt = 0
    while q:
        de = 1
        t = False
        for idx in range(1, len(q)):
            if q[0] < q[idx]:
                tmp = q.popleft()
                q.append(tmp)
                if NM[1] == 0:
                    NM[1] = len(q) - 1
                else:
                    NM[1] -= 1
                t = True
                break
        if t:
            continue
        q.popleft()
        cnt += 1
        if NM[1] == 0:
            print(cnt)
            break
        else:
            NM[1] -= 1
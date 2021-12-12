import sys

M, S = map(int, sys.stdin.readline().split())
#속도는 딕셔너리보다 set이다...!!!!!!!!
M_li = set([sys.stdin.readline().rstrip() for _ in range(M)])

result = 0
for _ in range(S):
    st = sys.stdin.readline().rstrip()
    if st in M_li:
        result += 1

print(result)
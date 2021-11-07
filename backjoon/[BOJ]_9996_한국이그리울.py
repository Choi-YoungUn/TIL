import sys

N = int(sys.stdin.readline())
tg = list(sys.stdin.readline().rstrip().split("*"))
real = len(tg)
for _ in range(N):
    st_list = sys.stdin.readline().rstrip()
    left = tg[0]
    right = tg[1]
    if len(left) + len(right) > len(st_list):
        print("NE")
        continue

    if st_list[:len(left)] == left and st_list[-len(right):] == right:
        print("DA")
    else:
        print("NE")
    
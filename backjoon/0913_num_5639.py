import sys

# peo = int(sys.stdin.readline())
# box = [list(map(int,sys.stdin.readline().split())) for _ in range(peo)]

temp = [0] 


box = []
count = 0

while count < 10000:
    try:
        temp = int(sys.stdin.readline())
        count += 1
    except:
        break
    box.append(temp)
temp = [0] * ((count + 1) * 2)
print(box)

def one(T):
    if T:

# 50, 30, 24, 5, 28, 45, 98, 52, 60
# 50 30 98 24 45 52 00 05 28 00 00 00 60 00 00
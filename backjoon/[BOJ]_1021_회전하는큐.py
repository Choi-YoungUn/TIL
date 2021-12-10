import sys
from collections import deque

NM = list(map(int, sys.stdin.readline().rstrip().split()))
num = list(map(int, sys.stdin.readline().rstrip().split()))
num_list = deque()
result = 0

for x in range(1, NM[0]+1):
    num_list.append(x)
pick = 0
while pick < len(num):
    idx = num_list.index(num[pick])
    if idx == 0:
        num_list.popleft()
        pick += 1
        continue
    elif idx <= (len(num_list) // 2):
        num_list.append(num_list.popleft())
        result += 1
    elif idx >(len(num_list) // 2):
        num_list.appendleft(num_list.pop())
        result += 1
        
print(result)
import sys

def check(room):
    global result
    now_room = room
    
    now_room -= B
    result += 1
    
    if now_room > 0:
        tmp = now_room // C
        if now_room % C :
            tmp += 1
        result += tmp
    

N = int(sys.stdin.readline().strip())
A = list(map(int, sys.stdin.readline().strip().split()))
B, C = map(int,sys.stdin.readline().strip().split())

result = 0
for x in A:
    check(x)
print(result)
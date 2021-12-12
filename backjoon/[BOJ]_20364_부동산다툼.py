import sys

NQ = list(map(int, sys.stdin.readline().split()))
tree = [0] * (NQ[0] + 1)
for _ in range(NQ[1]):
    num = int(sys.stdin.readline())
    stack = [num]
    #경로를 계산해주자
    while num > 1:
        stack.append(num // 2)
        num = num //2
    #경로대로 가보자! 
    while stack:
        #가는 경로에 막혀있으면 해당 위치 프린트!
        if tree[stack[-1]] == 1:
            print(stack[-1])
            break
        #경로의 끝 (원하는 땅)에 도착시!
        elif len(stack) == 1:
            tree[stack[-1]] = 1
            print('0')
            break
        
        stack.pop()
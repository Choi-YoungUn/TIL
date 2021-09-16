def color(n,k,answer):
    if(n/k == 2):
        return 2
    if(k == 1):
        return n
    if(answer[n][k] == 0):
        total = color(n-1,k,answer) + color(n-2,k-1,answer)
        answer[n][k] = total
        return total
    else:
        return answer[n][k]
        
n = int(input(""))
k = int(input(""))

answer = [[0]*(n+1) for i in range(n+1)]

if(n/2 < k):
    print(0)
else:
    print(color(n,k,answer)%1000000003)
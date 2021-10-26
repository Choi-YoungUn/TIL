import sys


def make(stings):
    if len(stings) == N-1:
        check.add(stings)
        return
    
    for x in range(N-1):
        if used[x] == 0:
            used[x] = 1
            make(stings + str(listss[x]))
            used[x] = 0


def excute(now_result, add_num, st):
    result = 0
    if st == '+':
        result = now_result + add_num
    elif st == '-':
        result = now_result - add_num
    elif st == '*':
        result = now_result * add_num
    elif st == '/':
        if now_result < 0:
            result = -((-now_result) // add_num)
        else:
            result = now_result // add_num
    return result


N = int(sys.stdin.readline())
num = list(map(int,sys.stdin.readline().split()))
cnts = list(map(int,sys.stdin.readline().split()))
listss = ['+'] * cnts[0] + ['-'] * cnts[1] + ['*'] * cnts[2] + ['/'] * cnts[3]
used = [0] * (N - 1)
check = set()
result_min = float('inf')
result_max = -float('inf')
min_st = ''
max_st =''
make('')
for strs in check:
    now_results = num[0]
    index = 1
    for now in strs:
        now_results = excute(now_results, num[index], now)
        index += 1

    if now_results > result_max:
        result_max = now_results
        max_st = strs
    if now_results < result_min:
        result_min = now_results
        min_st = strs
    
        
print(result_max)
print(result_min)
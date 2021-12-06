import sys

string = sys.stdin.readline().rstrip()

stack = []
idx_list = []

for st_idx in range(len(string)):
    
    try:
        if string[st_idx] == '(':
            stack.append(st_idx)
        elif string[st_idx] == ')':
            idx_list.append([stack.pop(), st_idx])
    except:
        continue

subset = [[]]
#부분합 만들기
for num in idx_list:
    size  = len(subset)
    for y in range(size):
        subset.append(subset[y] + [num])

li = set()
result = []
list_string = []
#입력을 리스트로변경
for x in string:
    list_string.append(x)

#리스트의 인덱스 위치값 없애기
for delete in subset[1:]:
    tmp = list_string[:]
    for a, b in delete:
        tmp[a] = ''
        tmp[b] = ''
    li.add(''.join(tmp))

for x in li:
    result.append(x)

result.sort()
for x in result:
    print(x)
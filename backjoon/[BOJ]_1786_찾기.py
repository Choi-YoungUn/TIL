import sys
def getPI(tg_st):
    j = 0
    for i in range(1, len(tg_st)):
        while j > 0 and tg_st[i] != tg_st[j]:
                j = pe[j - 1]
        if tg_st[i] == tg_st[j]:
            j += 1
            pe[i] = j

def check(to_st, tg_st):
    global result, idx
    getPI(tg_st)
    j = 0
    for i in range(len(to_st)):
        while j > 0 and to_st[i] != tg_st[j]:
                j = pe[j - 1]
        if to_st[i] == tg_st[j]:
            if j == len(tg_st) -1:
                result += 1
                idx.append(i -len(tg_st) + 2)
                j = pe[j]
                
            else:
                j += 1

total_st = sys.stdin.readline().rstrip()
tg_st = sys.stdin.readline().rstrip()
pe = [0 for _ in range(len(tg_st))]
result = 0
idx = []
check(total_st, tg_st)

print(result)
print(' '.join(list(map(str, idx))))

#####KMP  
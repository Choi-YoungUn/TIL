import sys
def getPI(tg_st):
    xidx = 0
    for i in range(1, len(tg_st)):
        while xidx > 0 and tg_st[i] != tg_st[xidx]:
                xidx = pe[xidx - 1]
        if tg_st[i] == tg_st[xidx]:
            xidx += 1
            pe[i] = xidx

def check(to_st, tg_st):
    getPI(tg_st)
    xidx = 0
    for i in range(len(to_st)):
        while xidx > 0 and to_st[i] != tg_st[xidx]:
                xidx = pe[xidx - 1]
        if to_st[i] == tg_st[xidx]:
            if xidx == len(tg_st) -1:
                return True
            else:
                xidx += 1
    return False
total_st = sys.stdin.readline().rstrip()
tg_st = sys.stdin.readline().rstrip()
pe = [0 for _ in range(len(tg_st))]

if check(total_st, tg_st):
    print(1)
else:
    print(0)

#####KMP  
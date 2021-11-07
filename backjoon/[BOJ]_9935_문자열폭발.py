import sys
long_str = sys.stdin.readline().rstrip()
tg_str = sys.stdin.readline().rstrip()
string = tg_str[-1]
tg_len = len(tg_str)
tmp = []
for str in long_str:
    tmp += str
    if len(tmp) < tg_len:
        continue
    if str != string:
        continue
    if tg_str == ''.join(tmp[-tg_len:]):
        del tmp[-tg_len:]

if len(tmp) > 0:
    print(''.join(tmp))
else:
    print('FRULA')
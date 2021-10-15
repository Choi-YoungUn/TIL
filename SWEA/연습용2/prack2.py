import sys


byte = sys.stdin.readline().strip()
temp = []
result = ''
for x in byte:
    t = format(int(x, 16), 'b')
    result += '0'*( 4 - len(t)) + t


print(result)

# 01D06079861D79F99F


format(value, 'b')
bin(value)[2:]
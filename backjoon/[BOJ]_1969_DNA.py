import sys

DNA = {
    "A" : 0,
    "C" : 1,
    "G" : 2,
    "T" : 3
}
DNA_T = ["A", "C", "G", "T"]

N, M =map(int, sys.stdin.readline().rstrip().split())
DNA_MAP = [sys.stdin.readline().rstrip() for _ in range(N)]
DNA_RESULT = [0] * M

for x in range(M):
    DNA_CNT = [0] * 4
    for y in range(N):
        DNA_CNT[DNA[DNA_MAP[y][x]]] += 1
    maxx = max(DNA_CNT)
    for j in range(4):
        if DNA_CNT[j] == maxx:
            DNA_RESULT[x] = DNA_T[j]
            break

result = 0
for x in range(M):
    ST = DNA_RESULT[x]
    for y in range(N):
        if ST != DNA_MAP[y][x]:
            result +=1

print("".join(DNA_RESULT))
print(result)

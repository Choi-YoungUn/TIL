import sys

#입력받기
N = int(sys.stdin.readline().rstrip())
S = [list(sys.stdin.readline().rstrip().split()) for _ in range(N)]
# q로 안하고 인덱스로 하기위한 변수
S_idx = [0] * N

L = list(sys.stdin.readline().rstrip().split())
result = 'Impossible'
#L의 단어 하나씩 앞에서 부터 검사한다
for word in L:
    #입력받은 문장 하나씩  불러서 앞에서부터 체크하자
    for idx in range(len(S)):
        #문장의 길이를 넘어간다면 다른문장 체크하자
        if len(S[idx]) <= S_idx[idx]:
            continue
        #확인하는 문장의 단어와 L의 단어를 비교해주고 맞다면 인덱스 하나 늘려주자
        if S[idx][S_idx[idx]] == word:
            S_idx[idx] += 1
            break
    else:
        break
else:
    result = 'Possible'
#앵무새가 단어 남은거 있니?
for idx in range(N):
    if S_idx[idx] != len(S[idx]):
        result = 'Impossible'
        break

print(result)
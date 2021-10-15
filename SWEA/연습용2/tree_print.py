# 트리형태 출력


# 인접 리스트로 트리를 저장
tree = [[] for _ in range(1000)]

# 입력
'''입력은
branch 개수,
root vertex 숫자,
parent child (branch 번 반복)
의 형태로 받는다
'''
B = int(input())  # branch 갯수
ROOT = int(input())  # root 숫자
for _ in range(B):
    parent, child = map(int, input().split())  # parent vertex, child vertex
    tree[parent].append(child)

# 여러 개의 자손 보유 시 줄 바꿈 후 indentation을 위해 앞에 넣어줘야 할 공백을 위한 stack
stack_line_index = [0]  # 자손이 여럿인 분기점마다 문자가 들어가야 하므로, 문자가 들어가야 하는 위치를 기록하는 stack
blanks = [0]  # 문자가 들어가야 하는 사이사이를 채워주는 공백 개수, blanks[i] = stack_line_index[i+1] - stack_line_index[i]


# dfs 사용
def dfs(now, line_index=8):  # now는 현재 vertex, line_index는 stack_line_index에 들어갈 값, 즉 문자가 시작할 위치이다.
    print(f'[{now:03}]', end='')
    # 자손이 있는 경우  --를 출력 이후 자손이 몇 명인지 본다.
    if tree[now]:
        print('--', end='')
        # 자손이 하나인 경우
        if len(tree[now]) == 1:
            print('---', end='')
            dfs(tree[now][-1], line_index + 10)  # 다음 vertex로 넘어간다. 다음 분기점은 10칸 이후 존재한다.
        # 자손이 여럿인 경우
        else:
            # 마지막 자손 제외 모든 자손에 대하여
            for child in tree[now][:-1]:
                stack_line_index.append(line_index)  # 문자가 들어가야 하는 위치 기록
                blanks.append(line_index - stack_line_index[-2] - 1)  # 이전에 기록된 위치와 현재 위치의 차만큼 공백이 들어가므로 이를 기록한다.
                print('+--', end='')
                dfs(child, line_index + 10)
            # 마지막 자손에 대하여
            print('L--', end='')
            dfs(tree[now][-1], line_index + 10)

    # 자손이 없는 경우, 줄을 바꾸고 공백과 공백 사이사이 문자를 추가한다.
    else:
        print()
        for blank in blanks[1:-1]:
            print(' ' * blank, end='')  # blanks에 기록된 만큼 공백 출력
            print('|', end='')  # 분기점 연결 선 출력
        print(' ' * blanks[-1], end='')  # 마지막 공백 출력
        # stack에 기록된 위치를 사용했으므로 제거
        stack_line_index.pop()
        blanks.pop()

dfs(ROOT)  # dfs 실행
"""
005_string: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('005_string_input.txt', 'rt', encoding='UTF-8')

#이동시킬 인덱스 반환 함수. 찾고자 하는 패턴과 틀린 문자를 입력
def moves_i(patten, char):
    # 패턴 속에서 틀린 문자가 있는지 뒷쪽부터 찾는다. 단. 맨뒤는 이미 검사 했으므로 그전부터.
    for i in range(len(patten) - 2 , -1, -1):
        #만약 찾았다면 전체길이 - 반복횟수 가 패턴을 이동시킬 인덱스값이다.
        if patten[i] == char:
            return len(patten) - 1 - i 
        #만약 없다면 패턴의 전체길이만큼 이동시켜준다
    return len(patten)

# 보이어 무어. 원하는 패턴과 전체 문장을 입력받는다
def moor(want_patten, full_text):
    #패턴의 길이와 전체 문자열의 길이를 저장, 현재 인덱스인 I에 0을 입력
    want = len(want_patten)
    full = len(full_text)
    i = 0
    #문제에서 찾고자하는 횟수 저장 변수
    counts = 0
    # 현제 위치가 전체 문장의 길이에서 패턴의 길이만큼 보다 크다면 그만둔다. 즉 더 찾아도 없다는 뜻
    while i <= full - want:
        #반복해줄 j를 설정. 패턴의 길이를 넣어준다. 
        j = len(want_patten) - 1
        #j가 맨뒤에서 하나씩 줄어듦으로 만약 계속 맞아서 -1이된다면 패턴이 끝났으므로 종료
        while j >= 0:
            #패턴의 맨뒷과 전체 문장의 맨뒷부터 차례로 검사 만약 다르다면
            if want_patten[j] != full_text[i + j]:
                #이동시킬 인덱스를 찾고자 함수에 넘겨준다
                move = moves_i(want_patten,full_text[i + want - 1])
                #무한루프가 되지 않도록 끝낸다
                break
            #문자가 같을 경우 -1해주는 부분
            j -= 1
            #만약 j가 -1 이라면 패턴을 찾은 것이므로 
        if j == -1:
            #카운트를 증가시켜주고 패턴만큼 뒤에서 부터 다시 찾기 시작하자
            counts += 1
            i += len(want_patten)
        else:
            #만약 j가 0 이상이라면 패턴이 틀렸다는 뜻이므로 그냥 이동시켜주자
            i += move
            #모든작업이 끝났다면 횟수를 반환
    return counts


T = 10
for test_case in range(1, T + 1):
    test = int(input())
    patten = input()
    text = input()
    print("#{} {}".format(test ,moor(patten, text)))



# #문자열 검색하는 보이어 무어 알고리즘
# def boyer_moore(pattern, text):
#     #길이를 자주쓰므로 길이를 받아둔다.
#     M = len(pattern)
#     N = len(text)
#     i = 0
#     #반복은 최대 긴텍스트 길이 - 작은텍스트 길이
#     while i <= N-M:
#         #보이어 무어 알고리즘은 뒤에서부터 접근하므로 pattern길이의 -1을 해준다.
#         #-1을 해주는 이유는 인덱스가 0부터 시작하기 때문이다.
#         j = M - 1
#         #뒤에서부터 검사하고 인덱스를 감소하는 형식이므로 0보다 이상일때만 동작한다.
#         while j >= 0:
#             #끝글자부터 비교하면서 같다면 하나씩 감소하면서 비교한다.
#             if pattern[j] != text[i+j]:
#                 #글자가 틀리다면 제일마지막 글자 기준으로 find 함수를 호출한다.
#                move = find(pattern, text[i + M - 1])
#                 break
#             j = j - 1
#         #인덱스가 -1이라는 뜻은 모든 글자가 맞았다는 이야기이다.
#         if j == -1:
#             #찾았으므로 true를 리턴한다.
#             return True
#             #인덱스 위치를 찾는다면
#             #return i
#         else:
#             #-1이 아니라면 글자를 못찾은 것이므로 find에서 넘겨준 값만큼 옆으로 이동한다.
#             i += move
#     #여기까지 왔다면 끝까지 찾지 못한것이므로 False를 리턴한다.
#     return False
#     #인데스 위치로 한다면
#     #return -1
 
# #불필요한 비교를 건너뛰기 위한 함수
# def find(pattern, char):
#     #마지막 부분과 일치하는 부분이 있는지 검색한다.
#     #마지막 부분은 이미 가능성이 없으므로 그전부터 검사한다.
#     for i in range(len(pattern)-2, -1, -1):
#         #마지막글자와 패턴중 일치하는 숫자가 있다면 그만큼 이동한다.
#         if pattern[i] == char:
#             return len(pattern) -i -1
#     #일치하는 글자가 없다면 패턴의 길이만큼 이동한다.
#     return len(pattern)
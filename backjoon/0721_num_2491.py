#point check.
#1.  지금 숫자와 이전 숫자 비교
#2. 비교후 크다면 길이 ++
#3. 비교후 작아진다면  이전 저장된 길이와 비교
#4. 길이 비교후 다시 다음것 진행
#5. 뒷쪽부터도 검사한다.

def check(num, nums):  #int 와 list로 나눠서 매개변수에 저장한다
    temp_long = 0  #제일 긴 길이 저장
    temp_now = 1    #현재 길이 저장
# 정방향으로 확인한다
    for a in range(0, num - 1):
        if nums[a] <= nums[a + 1]: # 현재값이 뒷값보다 작으면
            temp_now += 1          # 현재 길이 + 1
        else:                        # 현재값이 뒷값보다 크다면
            if temp_now > temp_long:   # 현재길이가 이전까지 제일긴 길이보다 길다면
                temp_long = temp_now  # 제일 긴 값으로 저장
            temp_now = 1             #다시 현재 길이 1로 초기화
    if temp_now > temp_long:      #for문이 끝났을 때 현재길이와 비교 후 저장
        temp_long = temp_now

    temp_now = 1
# 반대로 반복한다.
    for b in range(num - 1, 0, -1):  #뒤에서 부터 똑같이 저장한다. 단 제일긴 길이는 유지
        if nums[b - 1] >= nums[b]:
            temp_now += 1
        else:
            if temp_now > temp_long:
                temp_long = temp_now
            temp_now = 1
    if temp_now > temp_long:
        temp_long = temp_now

    return temp_long       # 지금까지 제일 긴 길이를 리턴해준다

num = int(input())     #첫 줄 입력 받기
num1 = list(map(int,(input().split())))  #두번째 줄 입력 받은 것을 리스트로 저장

print(check(num, num1))   #인자 값으로 int와 list 넘겨준다 그후 리턴 값을 출력한다.
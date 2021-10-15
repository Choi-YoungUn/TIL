test_case = int(input())
# int(value) : value를 정수로 바꾼다.
N = int(input())
Height = list(map(int, input().split()))
# input() <- 한줄 입력
# input().split() <- 한 줄 입력받고 띄어쓰기 단위로 쪼개기
# map(int, input().split()) <- 쪼갠 DATA들을 int(정수)로 각각 변환
# list(map(int, input().split())) <- 변환 data들을 list형태로 사용
print(Height[-4])

# input() <- 한 줄을 입력받는다.
# str.split() <- 띄어쓰기 단위로 쪼갬
# "7 4 2 0 0 6 0 7 0" -> 띄어쓰기 단위로 쪼개기
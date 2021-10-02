num = 4           # 사각형 갯수
k = []            #흰 바탕 만들 리스트
shadow = []          # 그림자진 곳
for sets in range(num):        #입력받기
  shadow.append(list(map(int,input().split())))

for x in range(100):     #흰 바탕 만들기 0으로 채워넣는다
  k.append([0] * 100)

for paper in range(num):     #사각형 갯수만큼
  for x in range(shadow[paper][0],  shadow[paper][2]):   # 시작 좌표부터 끝 좌표까지
    for y in range(shadow[paper][1], shadow[paper][3]):
      k[x][y] = 1          # 그림자를 1로 표시

temp = 0
for a in k:             #총 그림자 갯수 세기
  temp += a.count(1)
print(temp)           #갯수 출력
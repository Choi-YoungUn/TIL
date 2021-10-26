num = int(input())   #횟수 입력
temp = []
for getin in range(num):
    temp_1 = list(map(int,input().split()))  #A아이 입력
    temp_2 = list(map(int,input().split()))  #B아이 입력
    temp.append([temp_1, temp_2])       #해당 판 묶어서 입력
    
for fight in range(num):               
    temp[fight][0].pop(0)               #각 판의 딱지 총 갯수 삭제
    temp[fight][1].pop(0)               #제 코드에선 필요없는 수
    temp[fight][0].sort(reverse= 1)     #딱지 모양 정렬
    temp[fight][1].sort(reverse= 1)

    check = min(len(temp[fight][0]), len(temp[fight][1]))  #둘중 모양을 적개낸 아이 기준
    for op in range(check):
      if temp[fight][0][op] > temp[fight][1][op]:  #별 모양부터 비교 없다면 그다음모양
        print('A')                                  
        break
      elif temp[fight][0][op] < temp[fight][1][op]:
        print('B')
        break
    else:             # 한아이가 낸 모양 수만큼 다른아이도 똑같이 냈다면
      if len(temp[fight][0]) > len(temp[fight][1]): #누가더 많이 냄?
        print('A')
      elif len(temp[fight][0]) < len(temp[fight][1]):
        print('B')
      else:             #둘다 똑같은 갯수 똑같은 모양으로 냈다면 무승부.
        print('D')
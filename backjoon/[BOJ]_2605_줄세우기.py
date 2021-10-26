#point
#1. 학생들이 순서대로 서있음
#2. 첫 학생부터 뽑는데 자신을 기준으로 
   #뽑은만큼 앞으로 이동.
#3. 한줄로 string으로 출력.

num = int(input())
p = []

pick = list(map(int,input().split()))
    

peo = list(range(1,num +1))
say = ''
# pick = list(map(int, '0 1 1 3 2'.split()))

for n in range(num):
    peo.pop(n)
    peo.insert(n - pick[n], n + 1)
for a in range(num):
    say += str(peo[a]) + ' '
print(say)
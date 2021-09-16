num = int(input())
people = list(map(int, input().split()))
people.sort()
time = 0
for x in range(num):
    time += sum(people[0:x + 1])
    print(time)
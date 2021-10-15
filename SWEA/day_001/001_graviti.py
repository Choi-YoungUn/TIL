test_case = int(input())

for als in range(test_case):
    N = int(input())
    Height = list(map(int, input().split()))

    hi = 0
    for a in range(N - 1):
        temp = 0
        for x in range(a + 1, N):
            if Height[a] > Height[x]:
                temp += 1

        if hi < temp:
            hi = temp

    print("#{} {}".format(als + 1, hi))
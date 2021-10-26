n, k = map(int, input().split())
k_list = []
for x in range(n):
    k_list.append(int(input()))

def binary(target, lists, start, end):
    
    while start <= end:
        cutting = 0
        cut = (start + end) // 2
        for loop in lists:
            cutting += loop // cut
        if cutting >= target:
            start = cut + 1
        else:
            end = cut - 1
    return end

print(binary(k, k_list, 1, max(k_list)))

arr = [55, 7 ,78 ,12 ,42]
lists_len = len(arr)
end = len(arr) - 1
while end > 0:
    last_swap = 0
    for i in range(end):
        if arr[i] > arr[i + 1]:
            arr[i], arr[i + 1] = arr[i + 1], arr[i]
            last_swap = i
    end = last_swap

print(arr)

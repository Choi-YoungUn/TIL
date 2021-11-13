for tc in range(1, int(input()) + 1):
    string, num = input().split()
    num = int(num)
    len_string = len(string)
    idx = 1
    add_idx = []
    while idx <= num:
        add_idx.append(idx)
        idx = idx * len_string + 1

    result = []
    for x in add_idx[::-1]:
        print(x,(num - x) % len_string, string[(num - x) % len_string])


        result.append(string[(num - x) % len_string])
        num = (num - 1) // len_string
   
    res = ''.join(result[::-1])
    print(f'#{tc} {res}')

# 17 5 0 2   5하나추가  4 1 0
# 16 5 0 1   5두개추가  2 2 0
# 14 4 0 2             3 1 0
# 13 4 0 1             1 2 0
# 19 6 0 1             3 2 0
# 7  2 0 1             


kg = int(input())
three_real = kg // 3
three_add = kg % 3
five_real = 0
break_po = 0
if kg < 3:
    break_po = 1
else:
    if three_add == 2:
        if three_real >= 1:
            three_real -= 1
            five_real += 1
        else:
            break_po = 1
    elif three_add == 1:
        if three_real >= 3:
            five_real += 2
            three_real -= 3
        else:
            break_po = 1

    while three_real >= 5:
        three_real -= 5
        five_real += 3

if break_po == 1:
    print("-1")
else:
    print(three_real + five_real)


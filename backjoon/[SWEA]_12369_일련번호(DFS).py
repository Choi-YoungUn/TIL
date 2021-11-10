T = int(input().rstrip())
for tc in range(1, T+1):
    string = list(input().rstrip().split())
    st_list = []
    cnt = 1
    
    for x in string[0]:
        st_list.append(x)
        cnt += 1

    idx = 0
    limit = int(string[1])
    while cnt < limit:
        tg_st = st_list[idx]
        for st in string[0]:
            
            st_list.append(tg_st+st)
            if cnt >= limit:
                cnt += 100
                break
            cnt += 1
        idx += 1
    print("#{} {}".format(tc, st_list[-1]))
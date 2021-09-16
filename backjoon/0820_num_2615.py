def check(lists):
    win= [0, 0, 0]
    box = lists
    ad_x = [0, 1, 1, -1]
    ad_y = [1, 0, 1, -1]
    for x in range(19):
        for y in range(19):
            for check_xy in range(4):
                counts = 0
                for z in range(5):
                    next_x = x + ad_x[check_xy] * z
                    next_y = y + ad_y[check_xy] * z
                    if box[next_x][next_y] == box[x][y]:
                        counts += 1
                if counts == 5:
                    win[1], win[2] = x, y

            

                
boxx = [list(map(int, input().split())) for _ in range(19)]
result = check(boxx)
print(result[0])
print("{} {}".format(result[1], result[2]))
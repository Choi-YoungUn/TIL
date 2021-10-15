
def check(now, sum, path):
    if sum == 10:

        ch_box.add(tuple(path))
    if now == len(box):
        return
    if sum > 10:
        return
    
    if sum + box[now] <= 10:
        check(now + 1, sum + box[now], path + [box[now]])


    check(now + 1, sum, path)
        


box = [1,2,3,4,5,6,7,8,9,10]
ch_box = set()

check(0, 0, [])

print(ch_box)
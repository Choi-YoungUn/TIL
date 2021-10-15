"""
water_play: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('water_play_input.txt')


def water(now_month, now_cost):
    global tatal_cost

    if now_month > 12:
        if tatal_cost > now_cost:
            tatal_cost = now_cost
        return

    if tatal_cost < now_cost:
        return

    # #1일권
    # water(now_month + 1, now_cost + day * plan[now_month])

    # #한달권
    # water(now_month + 1, now_cost + month)

    # 하루와 한달 종합.
    water(now_month + 1, now_cost + min(day * plan[now_month],  month))

    #3달권
    water(now_month + 3, now_cost + th_mo)
    

T = int(input().strip())
for tc in range(1, T + 1):
    day, month, th_mo, year = map(int, input().split())
    plan = [0] + list(map(int, input().split()))
    tatal_cost = year

    water(1, 0)

    print("#{} {}".format(tc, tatal_cost))
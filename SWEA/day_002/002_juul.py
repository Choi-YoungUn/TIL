"""
002_juul: 문제명을 입력해주세요 :)
"""

import sys
sys.stdin = open('002_juul_input.txt')



# def juul(lists, num, one_num):
#     temp_lists = lists[:]
#     nums = num
#     temp_num = 0
#     if nums in temp_lists:
#         return 0
#     else:
#         for x in range(len(temp_lists) -1, -1, -1):
#             if temp_lists[x] < nums and temp_num < temp_lists[x]:
#                 temp_num = temp_lists[x]
#                 break
#         if temp_num == 0:
#             return  one_num
#         nums -= temp_num
#         temp_lists.remove(temp_num)
#     return juul(temp_lists, nums, one_num)

# num = int(input())
# lists = list(map(int,input().split()))

# lists.sort() 
# start = 1
# ends = sum(lists) + 1

# while start < ends:
#     result = juul(lists, start, start)
#     if result != 0:
#         print(result)
#         break
#     start += 1
# else:
#     print(ends)
#  ------------------------------------------
# num = int(input())
# lists = list(map(int,input().split()))

# def solution(weights):
#     weights.sort()
#     temp = weights[0]
#     for i in range(1, len(weights)):
#         if weights[i] - temp > 1:
#             break
#         else:
#             temp += weights[i]
    
#     return str(temp + 1)
    
# print(solution(lists))
# ----------------------------------------------
n = int(input())
a = list(map(int,input().split()))
a.sort()

b=1
for i in range(n):
    if b < a[i]:
        break
    b+= a[i]
print(b)

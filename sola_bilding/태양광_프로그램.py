# -*- coding: utf-8 -*-
"""태양광 프로그램.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1Ww1oRn5nJKdsXchMlRqHM-7YabUersK9
"""

import numpy as np
import pandas as pd
import math
import numbers

hiiii = 0

class build:
  def __init__(self, build_h, build_w, build_latitude, build_longitude, build_angle ):
    self.build_h = build_h  #건물 높이
    self.build_w = build_w   #건물에 설치할 태양광 패널 가로 길이
    self.build_latitude = build_latitude  #건물 위도
    self.build_longitude = build_longitude  #건물 경도
    self.build_angle = build_angle  #건물 각도
    self.build_h_get = [] #햇빛이 비추는지 여부 확인용
    self.app_h(build_h)

  def app_h(self,height): #건물 높이(m)마다 1을 넣고 1이면 일사량 계산 그림자이면 0으로 바꾸는 용도
    for x in range(0, height):
      self.build_h_get.append(1)
    
#건물 데이터 저장 클래스.

class sun: #시간별 태양위치
  def __init__(self, sun_angle, sun_azimuth, sun_time):
    self.sun_angle = sun_angle #태양 고도
    self.sun_azimuth = sun_azimuth #태양 방위각
    self.sun_time = sun_time #태양 시간

def sun_get(sola_angle, sun_power): #단순 발전 계산식 sola = 발전효율 해야하고, sun_power은 일사량
  all_time = 0
  angle = [75,85,93,97,99,98,93,86,77,65]
  for i in range(0, hei):
    if sel_buil.build_h_get[i] == 1:
      all_time += 1
  angledd = sola_angle//10 
  angledd = angle[angledd]

  sun_geting = angledd * 0.7 * sun_power * all_time 
  return sun_geting

class GeoUtil:  # 두 좌표 사이 거리 구하기 함수.
    """
    Geographical Utils
    """
    @staticmethod
    def degree2radius(degree):
        return degree * (math.pi/180)
    
    @staticmethod
    def get_harversion_distance(x1, y1, x2, y2, round_decimal_digits=5):
        """
        경위도 (x1,y1)과 (x2,y2) 점의 거리를 반환
        Harversion Formula 이용하여 2개의 경위도간 거래를 구함(단위:Km)
        """
        if x1 is None or y1 is None or x2 is None or y2 is None:
            return None
        assert isinstance(x1, numbers.Number) and -180 <= x1 and x1 <= 180
        assert isinstance(y1, numbers.Number) and  -90 <= y1 and y1 <=  90
        assert isinstance(x2, numbers.Number) and -180 <= x2 and x2 <= 180
        assert isinstance(y2, numbers.Number) and  -90 <= y2 and y2 <=  90

        R = 6371 # 지구의 반경(단위: km)
        dLon = GeoUtil.degree2radius(x2-x1)    
        dLat = GeoUtil.degree2radius(y2-y1)

        a = math.sin(dLat/2) * math.sin(dLat/2) \
            + (math.cos(GeoUtil.degree2radius(y1)) \
              *math.cos(GeoUtil.degree2radius(y2)) \
              *math.sin(dLon/2) * math.sin(dLon/2))
        b = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
        return round(R * b, round_decimal_digits)*1000 #m단위로 변경

    @staticmethod
    def get_euclidean_distance(x1, y1, x2, y2, round_decimal_digits=5):        
        """
        유클리안 Formula 이용하여 (x1,y1)과 (x2,y2) 점의 거리를 반환
        """
        if x1 is None or y1 is None or x2 is None or y2 is None:
            return None
        assert isinstance(x1, numbers.Number) and -180 <= x1 and x1 <= 180
        assert isinstance(y1, numbers.Number) and  -90 <= y1 and y1 <=  90
        assert isinstance(x2, numbers.Number) and -180 <= x2 and x2 <= 180
        assert isinstance(y2, numbers.Number) and  -90 <= y2 and y2 <=  90

        dLon = abs(x2-x1) # 경도 차이
        if dLon >= 180:   # 반대편으로 갈 수 있는 경우
            dLon -= 360   # 반대편 각을 구한다
        dLat = y2-y1      # 위도 차이
        return round(math.sqrt(pow(dLon,2)+pow(dLat,2)),round_decimal_digits)

def hi(space, angle, tmp_h):  #그림자가 지는 높이
  sel_sun_h = tmp_h - (space * math.tan(angle))
  if sel_sun_h <= 0:
    sel_sun_h = 0
  return sel_sun_h

final_angle = 0
def build_azimuth(x1, y1, x2,y2): #경, 위,경, 위
  x = GeoUtil.get_harversion_distance(x1,y1,x2,y2 )
  y = GeoUtil.get_harversion_distance(x1,y1,x1,y2 )
  
  if y1 == y2:
    if x1 < x2:
      final_angle = 90
    elif x1 > x2:
      final_angle = 270
    elif x1 == x2:
      final_angle = None
  elif y1 > y2:  #3, 4분면
    final_angle = math.acos(y/x)*(180/3.14)
    if x1 < x2:      # 4사분면
        final_angle = 180 - final_angle    #4사분면
    elif x1 > x2:
        final_angle = 180 + final_angle
    elif x1 == x2:
      final_angle = 180
  elif y1 < y2:
    final_angle = math.acos(y/x)*(180/3.14)
    if x1 > x2:
      final_angle = 360 - final_angle
  else:
    final_angle = math.acos(y/x)*(180/3.14)
      
 #시계방향 방위각
  return final_angle

build_data_set = pd.read_csv("/content/drive/My Drive/seoul_building.csv", thousands=',', encoding = 'euc_kr' )
sun_data_set = pd.read_csv("/content/drive/My Drive/임시 데이터.csv", thousands=',', encoding = 'euc_kr' )

build_data_set

building_data_set = [] # 데이터 저장
for x  in range(0,1029872):
  building_data_set.append(build(int(build_data_set['건물높이'][x]), 1, build_data_set['위도'][x], build_data_set['경도'][x], 0 ) )

poss = []            # 그림자 계산기!!!
def engine(times):
  for x in range(0,1029872): 
    b_spaced = GeoUtil.get_harversion_distance(sel_buil.build_longitude, sel_buil.build_latitude,
                                              building_data_set[x].build_longitude,
                                              building_data_set[x].build_latitude)
    if b_spaced <= 200:
      poss.append(build_azimuth(sel_buil.build_longitude, sel_buil.build_latitude, building_data_set[x].build_longitude,
                                building_data_set[x].build_latitude))
      if poss[-1] != None:
        if int(sun_data_set['방위각(도 분 초)'][times][:3])-10 <= int(poss[-1]):
          if int(sun_data_set['방위각(도 분 초)'][times][:3])+10 >= int(poss[-1]):
            heights = hi(b_spaced,int(sun_data_set['고도(도 분 초)'][times][:2]), building_data_set[x].build_h )
            if int(heights) > 0:
              for y in range(0,int(heights)):
                if y < len(sel_buil.build_h_get):
                  sel_buil.build_h_get[y] = 0
      if b_spaced <= 100:
        if poss[-1] != None:
          if int(sun_data_set['방위각(도 분 초)'][times][:3])-20 <= int(poss[-1]):
            if int(sun_data_set['방위각(도 분 초)'][times][:3])+20 >= int(poss[-1]):
              heights = hi(b_spaced,int(sun_data_set['고도(도 분 초)'][times][:2]), building_data_set[x].build_h )
              if int(heights) > 0:
                for y in range(0,int(heights)):
                  if y < len(sel_buil.build_h_get):
                    sel_buil.build_h_get[y] = 0

print("보고싶은 시간 6~20시")
times = int(input())
times = times - 6
print("위도를 입력")   #37.489350
lat = float(input())
print("경도를 입력")  #126.899996
longs = float(input())
print("건물 높이 입력")
hei = int(input())
sel_buil = build(hei, 1, lat, longs, 0 ) 
engine(times)
print(sun_get(60 , sun_data_set['일사(MJ/m2)'][times])) #설치된 각도, 일사량
for i in range(0, hei):
    if sel_buil.build_h_get[i] == 1:
      print(" {} 층 부터 햇빛이 듭니다".format(i+1))
      break

sun_get(60 , sun_data_set['일사(MJ/m2)'][times])
import requests as req
from bs4 import BeautifulSoup as bs

import selenium
from selenium import webdriver
from selenium.webdriver import ActionChains

from selenium.webdriver.common.keys import Keys
from selenium.webdriver.common.by import By

from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.support.ui import Select
from selenium.webdriver.support.ui import WebDriverWait


# 1. 띄울 url
URL = 'https://edu.ssafy.com/comm/login/SecurityLoginForm.do'

# 2. 페이지 열기
driver = webdriver.Chrome(executable_path='chromedriver')
driver.get(url=URL)
print('페이지 열기 성공')


# 3. id 입력
id = ' '
search_ID_box = driver.find_element_by_xpath('/html/body/div[1]/div/div/div[2]/form/div/div[2]/div[1]/div[1]/input')
search_ID_box.send_keys(id)
print('ID입력 성공')

# 4. password 입력
password = ' '
search_PASS_box = driver.find_element_by_xpath('/html/body/div[1]/div/div/div[2]/form/div/div[2]/div[1]/div[2]/input')
search_PASS_box.send_keys(password)
print('PASS 성공')

# 5. 로그인 클릭하기
posting_login = driver.find_element_by_xpath('/html/body/div[1]/div/div/div[2]/form/div/div[2]/div[3]/a')
posting_login.click()

# 6. 자동 출석체크
# posting_day_check = driver.find_element_by_xpath('/html/body/div[1]/div[1]/div[1]/section[1]/div/div[1]/div/div[2]/div[1]')
# posting_day_check.click()

# # 7. 강의실 들어가기
# posting_serch = driver.find_element_by_xpath('/html/body/div[1]/header/div[1]/div[2]/ul/li[2]/a')
# posting_serch.click()
# print('강의실 입장')

# # 7. 설문조사 들어가기
# posting_serch = driver.find_element_by_xpath('/html/body/div[1]/div[1]/div[1]/div[2]/div/ul/li[3]/a')
# posting_serch.click()

# surveys=driver.find_elements_by_class_name("icon-circle-state-scheduled")
# for i in surveys:
#     print(i.text)

# weekdays=['(월)','(화)','(수)','(목)','(금)','(토)','(일)']
# date=datetime.datetime.today().strftime('%y%m%d')
# CheckIn_Survey=date+weekdays[datetime.datetime.today().weekday()]+'_오전 건강현황 조사_6기'
# CheckOut_Survey=date+weekdays[datetime.datetime.today().weekday()]+'_오후 건강현황 조사_6기'
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

import datetime
#from datetime import pytz

#datetime.datetime.now(pytz.timezone('UTC'))
now = datetime.datetime.now()




# 1. 띄울 url
URL = 'https://edu.ssafy.com/comm/login/SecurityLoginForm.do'

# 2. 페이지 열기
driver = webdriver.Chrome(executable_path='chromedriver')
driver.get(url=URL)
print('페이지 열기 성공')


# 3. id 입력

search_ID_box = driver.find_element_by_xpath('/html/body/div[1]/div/div/div[2]/form/div/div[2]/div[1]/div[1]/input')

###### 이메일을 입력해 주세요
search_ID_box.send_keys('')
print('ID입력 성공')

# 4. password 입력

search_PASS_box = driver.find_element_by_xpath('/html/body/div[1]/div/div/div[2]/form/div/div[2]/div[1]/div[2]/input')

### 비밀번호를 입력해주세요
search_PASS_box.send_keys('')
print('PASS 성공')

# 5. 로그인 클릭하기
posting_login = driver.find_element_by_xpath('/html/body/div[1]/div/div/div[2]/form/div/div[2]/div[3]/a')
posting_login.click()
print('로그인 성공')


print(' ')
print(' ')

if now.hour == 8:
    if now.minute >= 30 and now.minute <= 59:
        
# 6. 자동 출석체크
        surveys=driver.find_elements_by_class_name("state")
        for i in surveys:

            if  '정상 출석' in i.text :
                print('정상 출석 하였습니다.')
            else:
                posting_day_check_in = driver.find_element_by_xpath('/html/body/div[1]/div[1]/div[1]/section[1]/div/div[1]/div/div[2]/div[1]')
                posting_day_check_in.click()

                posting_day_check_ent = driver.find_element_by_xpath('/html/body/div[3]/div/div/div[2]/div/button')
                posting_day_check_ent.click()
                print("출석 완료")


elif now.hour == 18:
    if now.minute >= 0 and now.minute <= 30:

#7. 자동 퇴실체크

        surveys=driver.find_elements_by_class_name("out")
        for i in surveys:
            if  '퇴실하기' in i.text :                
                posting_day_check = driver.find_element_by_xpath('/html/body/div[1]/div[1]/div[1]/section[1]/div/div[1]/div/div[2]/div[2]/a')
                posting_day_check.click()

                posting_day_check_ent = driver.find_element_by_xpath('/html/body/div[3]/div/div/div[2]/div/button')
                posting_day_check_ent.click()

                print('퇴실 완료')
            else:
                print("퇴실 불가")

else:
    print('입퇴실 시간이 아닙니다.\n')
    surveys=driver.find_elements_by_class_name("state")
    for i in surveys:
        if  '정상 출석' in i.text :
            print('정상 출석 하였습니다.')
        else:
            print("오늘 출석 실패....!")
    surveys=driver.find_elements_by_class_name("out")
    for i in surveys:
        if  '퇴실하기' in i.text :
            print('퇴실 가능!')
        else:
            print("정상퇴실 불가...지각이라도....")


print(' ')
print(' ')

# 8. 강의실 들어가기
posting_serch = driver.find_element_by_xpath('/html/body/div[1]/header/div[1]/div[2]/ul/li[2]/a')
posting_serch.click()
print('강의실 입장')

# 9. 설문조사 들어가기
posting_serch = driver.find_element_by_xpath('/html/body/div[1]/div[1]/div[1]/div[2]/div/ul/li[3]/a')
posting_serch.click()
print('설문조사 입장')

# 10. 페이지 수 체크
surveys=driver.find_elements_by_class_name("num")
co = 0
for i in surveys:
    co += 1
temp_page = 0
    
# 11. 미완료 설문 확인하기
print('설문조사 확인합니다\n')
count = 0
for a in range(co):
    surveys=driver.find_elements_by_class_name("mql-etc")
    for i in surveys:
        if '설문참여' in i.text:
            count += 1
            temp_page = a
    if a < co -1:
        posting_serch_next = driver.find_element_by_xpath('/html/body/div[1]/form/div/div[2]/div/div/div/ul/li[7]/a/i')
        posting_serch_next.click()
else:
    posting_serch_first_p = driver.find_element_by_xpath('/html/body/div[1]/form/div/div[2]/div/div/div/ul/li[1]/a/i')
    posting_serch_first_p.click()
       
# 12. 미완료 설문 페이지로 이동 & 결과 확인
if count != 0:
    print(f'미완료 설문이 총 {count}개 있습니다')
    print('처음 미완료 설문 페이지로 이동!')
    for b in range(temp_page):
        posting_serch_next = driver.find_element_by_xpath('/html/body/div[1]/form/div/div[2]/div/div/div/ul/li[7]/a/i')
        posting_serch_next.click()
else:

    driver.close()
    print('모든 설문 완료!')


print('------------------------')
print('프로그램 종료')
#/html/body/div[1]/form/div/div[2]/div/div/div/ul/li[4]/a
#/html/body/div[1]/form/div/div[2]/div/div/div/ul/li[5]/a
#/html/body/div[1]/form/div/div[2]/div/div/div/ul/li[6]/a

#print(f"설문 해야할 갯수 = {count}")
# weekdays=['(월)','(화)','(수)','(목)','(금)','(토)','(일)']
# date=datetime.datetime.today().strftime('%y%m%d')
# CheckIn_Survey=date+weekdays[datetime.datetime.today().weekday()]+'_오전 건강현황 조사_6기'
# CheckOut_Survey=date+weekdays[datetime.datetime.today().weekday()]+'_오후 건강현황 조사_6기'

#/html/body/div[1]/form/div/div[2]/div/div/ul/li[5]/div/div[3]/strong

#설문 참여 xpth
#/html/body/div[1]/form/div/div[2]/div/div/ul/li[6]/div/div[3]/a
# class = mql-etc  dkfodml 'btn-mql-submit' 이다.
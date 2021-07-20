//**************** DcMotor.c **********************

#include "main.h"
#include  <math.h>
#include <stdlib.h>
#include "Dcmotor.h"

 //Controller 제어기 변수

typeDcMotor  DcMotor1;//모터 관련 변수
typeController Controller1;//제어기관련 변수
typeBackup   Backup1;//백업대상

void DcMotor1SetDutyPulse(TIM_HandleTypeDef *htim, int16_t pulse)
{
  //PWM duty를 100(ARR값)으로 제한
  if(pulse>=100) pulse=100;
  else if(pulse<-100) pulse=-100;
  //Motor Driver Enable <= 0
  DcMotor1Enable();
 
  //  DC Motor  Direction +PWMx1개를 사용하는 경우

  if( pulse>=0)
  { 
    DcMotor1DirCw() ;
    //TIMx->CCR1=pulse; 
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1, pulse);
  } 
  else
  {
    DcMotor1DirCcw() ;
    //TIMx->CCR1= -1*pulse; 
    __HAL_TIM_SET_COMPARE(htim, TIM_CHANNEL_1,  -1*pulse);
  }  
   HAL_TIM_PWM_Start(htim, TIM_CHANNEL_1); 
}
//모터 회전수
void CalculateMotorRevolution(typeDcMotor *motor)
{
   motor->MotorRevolution =  (float)motor->Encoder32 /(float)MOTOR_1REVOLUTION_PULSE;
}

//휠회전수
void CalculateWheelRevolution(typeDcMotor *motor)
{
   motor->WheelRevolution =  (float)motor->Encoder32 /(float)WHEEL_RESOLUTION;
}

//모터 회전속도 RPS Rev/sec
void CalculateMotorRPS(typeDcMotor *motor)
{
  motor->MotorRps = (float)motor->Encoder32Diff*Fsample/(float)MOTOR_1REVOLUTION_PULSE;
}

//모터 회전속도 RPM
void CalculateMotorRPM(typeDcMotor *motor)
{
   motor->MotorRpm = (float)motor->Encoder32Diff*Fsample/(float)MOTOR_1REVOLUTION_PULSE*60;
}
//기어휠 회전속도 RPS
void CalculateWheelRPS(typeDcMotor *motor)
{
   motor->WheelRps = (float)motor->Encoder32Diff*Fsample/(float)WHEEL_RESOLUTION;
}
//기어휠 회전속도 RPM
void CalculateWheelRPM(typeDcMotor *motor)
{
   motor->WheelRpm = (float)motor->Encoder32Diff*Fsample/(float)WHEEL_RESOLUTION*60;
}

//실수값을 최대 limit이내로 int16형으로 변환

//http://ehpub.co.kr/round-roundf-roundl-%ED%95%A8%EC%88%98/

int16_t FloatToInt16Limit(float f, int limit) 
{
  int16_t  u;
  float f1;
 #if 1
  //소수점 이하 자리를 사사오입해서 소수점자리가 0인 실수형
    f1 = roundf(f);
   //u값을   -U_MAX<= u  <=+U_MAX로 제한
   if( f1 >=0)      u= (uint16_t) MIN(f1, U_MAX) ;// 30<=(30, 100), 100<=(150, 100)
    else   u = (uint16_t) MAX (f1, -U_MAX) ; // -30<=(-30, -100), -100<=(-150, -100)
 #else 

   if( f >=0){

      u= f >=limit  ?  limit : (int16_t)(f  + 0.5 ) ; 

   }else{

      u= f <=-limit ?  -limit :(int16_t)(f  - 0.5 ) ; 

   }

#endif

   return u;

}

//int16 정수값을 최대 limit이내로 int16형으로 변환

int16_t LimitInt16(int16_t input, int16_t  limit) 

{

   int16_t  result;

   if(input >=0){

      result = input <= limit?   input:  limit ; 

   }else{

     result = input  >= -1*limit ? input:  -1*limit; 

   }

   return result;

}

 

int32_t LimitInt32(int32_t input, int32_t  limit) 

{

   int32_t  result;

   if(input >=0){

      result = input <= limit?   input:  limit ; 

   }else{
     result = input  >=-1*limit ? input:  -1*limit; 
   }
   return result;
}
 
float LimitFloat(float input, float limit) 
{
   float result;
   if(input >=0){
      result = input <= limit?   input:  limit ; 
   }else{
     result = input  >= -1*limit ? input:  -1*limit; 
   }
   return result;  
}

int16_t AvoidDeadzone(int16_t u, int16_t requirement_plus, int16_t requirement_minus)
{
   int16_t result;
   if(u>0)  result = MAX(u, requirement_plus); //양의 PWM펄스 최소값 입력
   else if(u<0) result = MIN(u, requirement_minus); //음의 PWM펄스 최소값 입력
   else result = 0;
   return result;
}
//**************** DcMotor.c **********************

#include "main.h"
#include  <math.h>
#include <stdlib.h>
#include "Dcmotor.h"

 //Controller ����� ����

typeDcMotor  DcMotor1;//���� ���� ����
typeController Controller1;//�������� ����
typeBackup   Backup1;//������

void DcMotor1SetDutyPulse(TIM_HandleTypeDef *htim, int16_t pulse)
{
  //PWM duty�� 100(ARR��)���� ����
  if(pulse>=100) pulse=100;
  else if(pulse<-100) pulse=-100;
  //Motor Driver Enable <= 0
  DcMotor1Enable();
 
  //  DC Motor  Direction +PWMx1���� ����ϴ� ���

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
//���� ȸ����
void CalculateMotorRevolution(typeDcMotor *motor)
{
   motor->MotorRevolution =  (float)motor->Encoder32 /(float)MOTOR_1REVOLUTION_PULSE;
}

//��ȸ����
void CalculateWheelRevolution(typeDcMotor *motor)
{
   motor->WheelRevolution =  (float)motor->Encoder32 /(float)WHEEL_RESOLUTION;
}

//���� ȸ���ӵ� RPS Rev/sec
void CalculateMotorRPS(typeDcMotor *motor)
{
  motor->MotorRps = (float)motor->Encoder32Diff*Fsample/(float)MOTOR_1REVOLUTION_PULSE;
}

//���� ȸ���ӵ� RPM
void CalculateMotorRPM(typeDcMotor *motor)
{
   motor->MotorRpm = (float)motor->Encoder32Diff*Fsample/(float)MOTOR_1REVOLUTION_PULSE*60;
}
//����� ȸ���ӵ� RPS
void CalculateWheelRPS(typeDcMotor *motor)
{
   motor->WheelRps = (float)motor->Encoder32Diff*Fsample/(float)WHEEL_RESOLUTION;
}
//����� ȸ���ӵ� RPM
void CalculateWheelRPM(typeDcMotor *motor)
{
   motor->WheelRpm = (float)motor->Encoder32Diff*Fsample/(float)WHEEL_RESOLUTION*60;
}

//�Ǽ����� �ִ� limit�̳��� int16������ ��ȯ

//http://ehpub.co.kr/round-roundf-roundl-%ED%95%A8%EC%88%98/

int16_t FloatToInt16Limit(float f, int limit) 
{
  int16_t  u;
  float f1;
 #if 1
  //�Ҽ��� ���� �ڸ��� �������ؼ� �Ҽ����ڸ��� 0�� �Ǽ���
    f1 = roundf(f);
   //u����   -U_MAX<= u  <=+U_MAX�� ����
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

//int16 �������� �ִ� limit�̳��� int16������ ��ȯ

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
   if(u>0)  result = MAX(u, requirement_plus); //���� PWM�޽� �ּҰ� �Է�
   else if(u<0) result = MIN(u, requirement_minus); //���� PWM�޽� �ּҰ� �Է�
   else result = 0;
   return result;
}
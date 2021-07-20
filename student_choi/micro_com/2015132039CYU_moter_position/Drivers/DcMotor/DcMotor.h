//***************
//*   DcMotor.h  
//****************
#include "main.h"

#define DIR_CW        GPIO_PIN_RESET
#define DIR_CCW       GPIO_PIN_SET

#define MOTOR_ENCODER_PPR    512
#define ENCODER_MULTIPLE_RATIO          4
#define MOTOR_1REVOLUTION_PULSE  (MOTOR_ENCODER_PPR * ENCODER_MULTIPLE_RATIO)
#define MOTOR_GEAR_RATIO      4
#define WHEEL_RESOLUTION         (MOTOR_1REVOLUTION_PULSE * MOTOR_GEAR_RATIO)      

//DC Motor Enable/Disable
#define DcMotor1Enable()        HAL_GPIO_WritePin(DCMOT1_EN_GPIO_Port, DCMOT1_EN_Pin,  GPIO_PIN_RESET)
#define DcMotor1Disable()       HAL_GPIO_WritePin(DCMOT1_EN_GPIO_Port, DCMOT1_EN_Pin,  GPIO_PIN_SET)
//DC Motor Diection
#define DcMotor1DirCw()         HAL_GPIO_WritePin(DCMOT1_DIR_GPIO_Port, DCMOT1_DIR_Pin, DIR_CW)
#define DcMotor1DirCcw()        HAL_GPIO_WritePin(DCMOT1_DIR_GPIO_Port, DCMOT1_DIR_Pin, DIR_CCW)
//DC Motor Read Encoder 16bit ��ȣ
#define DcMotor1ReadEncoder()   ( (int16_t) __HAL_TIM_GET_COUNTER(&htim3))
//DC Motor Duty Pulse
void DcMotor1SetDutyPulse(TIM_HandleTypeDef *htim, int16_t pulse);


#define ENCODER_EXTI_DISABLE()   HAL_NVIC_DisableIRQ(EXTI9_5_IRQn)
#define ENCODER_EXTI_ENABLE()    HAL_NVIC_EnableIRQ(EXTI9_5_IRQn)
#define ENCODER_EXTI_FLAG_CLEAR()     __HAL_GPIO_EXTI_CLEAR_FLAG(EXTI9_5_IRQn)
#define ENCODER_EXTI_FLAG_SET()         __HAL_GPIO_EXTI_SET_FLAG(EXTI9_5_IRQn)

#define READ_TIMER_CNT()   ( (uint16_t) __HAL_TIM_GET_COUNTER(&htim6))

#define Fsample  1000.
#define Tsample  (1./Fsample)
#define RECORD_MAX  500
#define U_MAX  100    

//���Ͱ��� ���� 
typedef struct {  
  int16_t Encoder16;      //16��Ʈ�� ���ڴ���
  int16_t Encoder16Old;
  int16_t Encoder16Diff;
  int32_t Encoder32;    //32��Ʈ�� ���ڴ���
  int32_t Encoder32Old;
  int32_t Encoder32Diff;
  
  //������ ȸ����
  float   MotorTurns;
  float   MotorRevolution;
  //���� ȸ����
  float   WheelTurns;
  float   WheelRevolution;

  float    MotorRps;   // ������  Rev / Sec
  float    MotorRpm; // ������  Rev / Min=MotorRps*60
  float    WheelRps;  // ����  Rev / Sec =MotorRps/����
  float    WheelRpm; // ����  Rev / Min = WheelRps*60
} typeDcMotor;

typedef struct{
   int loop;

  int32_t Output32;   //32bit��  �����������(������Է�)
  int32_t Target32;    //32bit��  ���͸�ǥ���(������Է�)
  float    OutputFloat;  //float  �����������(������Է�)
  float    TargetFloat;  //float  ���͸�ǥ���(������Է�)

   //int32�� �����
   int32_t  Error32;
   int32_t  ErrorSum32;
   int32_t  ErrorOld32;
   int32_t  ErrorDiff32;
   int32_t  ErrorDiffOld32;
   
   //float�� �����
   float  ErrorFloat;
   float  ErrorSumFloat;
   float  Errorfloat;  
   float  ErrorOldFloat;
   float  ErrorDiffFloat;
   float  ErrorDiffOldFloat;

   float    f;//PWM �Ǽ��� ��갪
   int16_t  U; //PWM ������ ��°� <=U_MAX(100)
   int16_t  u;
}typeController;

typedef struct {
	int32_t RecordOutput[RECORD_MAX];
	int32_t RecordU[RECORD_MAX];
	int32_t RecordError[RECORD_MAX];
	int32_t RecordErrorSum[RECORD_MAX];
	int32_t RecordErrorDiff[RECORD_MAX];
	float floatData1[RECORD_MAX];
	float floatData2[RECORD_MAX];
}typeBackup;

//�Ǽ�f�� int16���� ��ȯ�ϴµ� limit�̳��� ����
int16_t  FloatToInt16Limit(float f, int limit) ;

//init16�� ������ limt�̳��� ����
int16_t LimitInt16(int16_t input, int16_t  limit) ;

// int32�� input�������� limit���� ����
int32_t LimitInt32(int32_t input, int32_t  limit) ;

//�Ǽ� input���� limit�� ����
float LimitFloat(float input, float limit) ;

//Motor Deadzone ���ϱ�
int16_t AvoidDeadzone(int16_t u, int16_t requirement_plus, int16_t requirement_minus);

#define ARRAY_SIZE(x) ( sizeof((x))/sizeof((x)[0]) ) // �迭�� ����
#define ABS(x)        ( ((x)<0)?-(x):(x) ) // ���밪
#define SQUARE(x)     ( (x)*(x) ) // ������
//#define UPCASE(c)     ( ((c)>='a'&&(c)<='z')?(c)-('a'-'A'):(c) ) // �ҹ��� -> �빮��
//#define LOWCASE(c)    ( ((c)>='A'&&(c)<='z')?(c)+('a'-'A'):(c) ) // �빮�� -> �ҹ���

//2���� �ִ밪 ����
#define MAX(x,y)      ( (x)>(y)?(x):(y) ) // �ִ� ��
//2���� �ּҰ� ����
#define MIN(x,y)      ( (x)<(y)?(x):(y) ) // �ּ� ��



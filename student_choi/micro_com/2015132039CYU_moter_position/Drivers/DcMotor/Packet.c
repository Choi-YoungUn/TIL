///////////////////////////////////////////////////////
//
//  Programmed by �̾��񱳼�
//
////////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "main.h"

#include "DcMotor.h"
#include "DcMotorExtern.h"

#include "circular-byte-buffer.h"

#include "Packet.h"

//��Ŷ ����
uint16_t countPacket=0;

extern struct{
   float Kp;
   float Ki;
   float Kd;
}PidParam;

extern enum {
  STATE_IDLE = 0,
  STATE_RUN_SAVE,
  STATE_NORUN_PRINT,
  STATE_RUN_ONLY,  
} RunState;

extern TIM_HandleTypeDef htim4;

extern TIM_HandleTypeDef htim9;

/*
�����ۿ��� ��Ŷ ����
atoi, atof, strtod, strtof �� ����
https://www.ibm.com/support/knowledgecenter/ko/ssw_ibm_i_73/rtref/strtod.htm
https://dojang.io/mod/page/view.php?id=387
*/
int PacketExtractFromBuffer(circ_bbuf_t *circ_buff, typePacket *packet)
{
  int len=0;
  uint8_t ch;
//  circ_bbuf_pop(circ_bbuf_t *c, uint8_t *data);
  len=0;
  do{
    circ_bbuf_pop(circ_buff, &ch);
    packet->buffer[len++] = ch;
    //= strlen(packet->buffer);
  } while(ch);
  packet->len= strlen(packet->buffer);
  countPacket--;
  return len;
}

/*
atoi, atof, strtod, strtof �� ����
https://www.ibm.com/support/knowledgecenter/ko/ssw_ibm_i_73/rtref/strtod.htm
https://dojang.io/mod/page/view.php?id=387
*/
  int32_t target;
void PacketParsing(typePacket *packet)
{ 
  int len = strlen(packet->buffer);
  int16_t count;

  char *end;
  switch( toupper(packet->buffer[0]) ){
     case 'K' ://Kp�� ����
         //strtof : string to float�� ��ȯ�ϴ� �Լ�, �̸� �ݺ������� ��밡��
         PidParam.Kp = strtof( packet->buffer+1, &end );
         PidParam.Ki = strtof(end, &end );
         PidParam.Kd = strtof(end, &end );
         
          //���� ����
         printf("Kp=%1c %10.3f %10.3f %10.3f \r\n", packet->buffer[0], PidParam.Kp, PidParam.Ki, PidParam.Kd);
         break;

     case 'E' ://Encoder�� ����
         count = atoi( packet->buffer+1 );
         //���ڴ����� count�� ����
          __HAL_TIM_SET_COUNTER(&htim4,   count); 
         //���� ����
         printf("Encoder=%1c %10d\r\n", packet->buffer[0], count);
         break;
         
     case 'R' ://// idlemode=>run
         Controller1.loop = 0;
         LCD_Plot_Axis();//LCD�� �׷��� �ʱ�ȭ�� �׸��� 
         RunState = STATE_RUN_SAVE;
          //���� ����
          //�ʱ�ȭ  .....
         printf("Run\r\n");
         break; 

     case 'T' ://Target
         target = atoi( packet->buffer+1 );         
         Controller1.Target32= target;
          //���� ����
         printf("Target=%1c %8d\r\n", packet->buffer[0], Controller1.Target32);;
         break; 

      case 'I' ://Idle (����)
        // Idle mode
        RunState = STATE_IDLE;
        Controller1.loop =0;

        //���� ����
         printf("Idle \r\n");
         break; 
  } 
}


///////////////////////////////////////////////////////
//
//  Programmed by 이양희교수
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

//패킷 갯수
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
링버퍼에서 패킷 추출
atoi, atof, strtod, strtof 등 연습
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
atoi, atof, strtod, strtof 등 연습
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
     case 'K' ://Kp값 변경
         //strtof : string to float로 변환하는 함수, 이를 반복적으로 사용가능
         PidParam.Kp = strtof( packet->buffer+1, &end );
         PidParam.Ki = strtof(end, &end );
         PidParam.Kd = strtof(end, &end );
         
          //추후 삭제
         printf("Kp=%1c %10.3f %10.3f %10.3f \r\n", packet->buffer[0], PidParam.Kp, PidParam.Ki, PidParam.Kd);
         break;

     case 'E' ://Encoder값 변경
         count = atoi( packet->buffer+1 );
         //엔코더값을 count로 변견
          __HAL_TIM_SET_COUNTER(&htim4,   count); 
         //추후 삭제
         printf("Encoder=%1c %10d\r\n", packet->buffer[0], count);
         break;
         
     case 'R' ://// idlemode=>run
         Controller1.loop = 0;
         LCD_Plot_Axis();//LCD에 그래프 초기화면 그리기 
         RunState = STATE_RUN_SAVE;
          //추후 삭제
          //초기화  .....
         printf("Run\r\n");
         break; 

     case 'T' ://Target
         target = atoi( packet->buffer+1 );         
         Controller1.Target32= target;
          //추후 삭제
         printf("Target=%1c %8d\r\n", packet->buffer[0], Controller1.Target32);;
         break; 

      case 'I' ://Idle (비동작)
        // Idle mode
        RunState = STATE_IDLE;
        Controller1.loop =0;

        //추후 삭제
         printf("Idle \r\n");
         break; 
  } 
}


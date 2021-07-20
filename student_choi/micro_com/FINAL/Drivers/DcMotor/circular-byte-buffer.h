/******************************************************************************

                  Copyright (c) 2018 EmbedJournal

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

    Author : Siddharth Chandrasekaran
    Email  : siddharth@embedjournal.com
    Date   : Sun Aug  5 09:42:31 IST 2018

******************************************************************************/
// https://embedjournal.com/implementing-circular-buffer-embedded-c/
// https://github.com/EmbedJournal/c-utils

#ifndef __CIRCULAR_BYTE_BUFFER_H_
#define __CIRCULAR_BYTE_BUFFER_H_

#include <stdint.h>
//원형버퍼 구조체형 선언
typedef struct {
    uint8_t * const buffer;//버퍼공간
    int head; // 데이터의 시작위치
    int tail;  // 데이터의 꼬리 비어있는 위치
    const int maxlen; // 최대저장가능 크기
    int full; //다 채워져 있는지?
} circ_bbuf_t;

//버퍼 생성 매크로
#define CIRC_BBUF_DEF(x,y)                \
    uint8_t x##_data_space[y+1];          \
    circ_bbuf_t x = {                     \
        .buffer = x##_data_space,         \
        .head = 0,                        \
        .tail = 0,                        \
        .maxlen = y+1 ,                    \
        .full = 0                         \
    }

/*
 * Method: circ_buf_pop :버퍼에 내용 추출
 * Returns:
 *  0 - Success
 * -1 - Empty
 */
int circ_bbuf_pop(circ_bbuf_t *c, uint8_t *data);


/*
 * Method: circ_buf_push : 버퍼에 내용 삽입
 * Returns:
 *  0 - Success
 * -1 - Out of space
 */
int circ_bbuf_push(circ_bbuf_t *c, uint8_t data);

/*
 * Method: circ_bbuf_free_space
 * Returns: number of bytes available
 */
int circ_bbuf_free_space(circ_bbuf_t *c);

#endif /* __CIRCULAR_BYTE_BUFFER_H_ */

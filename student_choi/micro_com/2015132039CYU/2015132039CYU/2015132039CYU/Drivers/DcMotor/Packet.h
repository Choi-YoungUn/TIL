//#include "circular-generic-buffer.h"
#include "circular-byte-buffer.h"

#define PACKET_BUFFER_RX_MAX 30

#define ASCII_NUL      0x00
#define ASCII_SOH      0x01
#define ASCII_STX      0x02
#define ASCII_ETX      0x03
#define ASCII_EOT      0x04
#define ASCII_CR       0x0d
#define ASCII_LF       0x0a

#define PACKET_START    ASCII_STX
#define PACKET_END      ASCII_CR

typedef struct {
  int16_t len;
  char buffer[PACKET_BUFFER_RX_MAX];
} typePacket;

int PacketExtractFromBuffer(circ_bbuf_t *circ_buff, typePacket *packet);
void PacketParsing(typePacket *packet);


